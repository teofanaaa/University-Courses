package webapp;

import javafx.util.Pair;
import webapp.model.Utilizator;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.http.HttpSession;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ApplicationManagement implements ServletContextListener {
    private static Connection connection;
    private static ServletContext application;

    public static List<Utilizator> getUtilizatori() {
        List<Utilizator> list = new ArrayList<>();
        PreparedStatement preparedStatement = null;
        try {
            preparedStatement = connection.prepareStatement(
                    "SELECT username, path_avatar, datan, descriere FROM utilizatori");

            ResultSet rs = preparedStatement.executeQuery();

            while (rs.next()) {
                String username = rs.getString("username");
                String path_avatar = rs.getString("path_avatar");
                Long datan = rs.getLong("datan");
                String descriere = rs.getString("descriere");
                Utilizator utilizator = Utilizator.builder()
                        .username(username)
                        .path_avatar(path_avatar)
                        .datan(datan)
                        .descriere(descriere)
                        .build();
                list.add(utilizator);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    public static boolean schimbaParola(String username, Long datan, String nouaParola) {
        boolean corect = varificaCredentiale(username, datan);
        if (corect) {
            PreparedStatement preparedStatement;
            try {
                preparedStatement = connection.prepareStatement(
                        "UPDATE utilizatori SET password = ? WHERE username = ?");
                preparedStatement.setString(1, nouaParola);
                preparedStatement.setString(2, username);
                preparedStatement.execute();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return corect;
    }

    private static boolean varificaCredentiale(String username, Long datan) {
        PreparedStatement preparedStatement = null;
        try {
            preparedStatement = connection.prepareStatement("SELECT datan FROM utilizatori WHERE username=?");

            preparedStatement.setString(1, username);
            System.out.println(username);
            ResultSet rs = preparedStatement.executeQuery();

            if (rs.next() && rs.getString("datan").equals(datan)) {
                return true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void setDetalii(String username, String descriere, Long datan) {
        PreparedStatement preparedStatement;
        try {
            preparedStatement = connection.prepareStatement(
                    "UPDATE utilizatori SET descriere = ?, datan = ? WHERE username = ?");
            preparedStatement.setString(1, descriere);
            preparedStatement.setLong(2, datan);
            preparedStatement.setString(3, username);
            preparedStatement.execute();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static List<Utilizator> getAltiUtilizatori(String usernameUs) {
        List<Utilizator> list = new ArrayList<>();
        PreparedStatement preparedStatement = null;
        try {
            preparedStatement = connection.prepareStatement(
                    "SELECT username, path_avatar, datan, descriere FROM utilizatori WHERE username <> ?");
            preparedStatement.setString(1, usernameUs);
            ResultSet rs = preparedStatement.executeQuery();

            while (rs.next()) {
                String username = rs.getString("username");
                String path_avatar = rs.getString("path_avatar");
                Long datan = rs.getLong("datan");
                String descriere = rs.getString("descriere");
                Utilizator utilizator = Utilizator.builder()
                        .username(username)
                        .path_avatar(path_avatar)
                        .datan(datan)
                        .descriere(descriere)
                        .build();
                list.add(utilizator);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    public static void addVot(String username, Integer nota) {
        PreparedStatement preparedStatement;
        try {
            preparedStatement = connection.prepareStatement(
                    "INSERT INTO voturi(username, rating) VALUES (?,?)");
            preparedStatement.setString(1, username);
            preparedStatement.setInt(2, nota);
            preparedStatement.execute();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static List<Pair<String,Double>> getCeiMaiTari() {
        List<Pair<String,Double>> list = new ArrayList<>();
        PreparedStatement preparedStatement = null;
        try {
            preparedStatement = connection.prepareStatement(
                    "SELECT username, AVG(rating) as nr FROM voturi GROUP BY username ORDER BY nr asc LIMIT 5");

            ResultSet rs = preparedStatement.executeQuery();

            while (rs.next()) {
                String username = rs.getString("username");
                Double nr = rs.getDouble("nr");
                list.add(new Pair<String, Double>(username, nr));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    public static List<Utilizator> getTopUsers() {
        List<Utilizator> list = new ArrayList<>();
        for (Pair<String,Double> pereche : getCeiMaiTari()) {
            PreparedStatement preparedStatement = null;
            try {
                preparedStatement = connection.prepareStatement(
                        "SELECT path_avatar, datan, descriere FROM utilizatori WHERE username = ?");
                preparedStatement.setString(1, pereche.getKey());
                ResultSet rs = preparedStatement.executeQuery();

                while (rs.next()) {
                    String path_avatar = rs.getString("path_avatar");
                    Long datan = rs.getLong("datan");
                    String descriere = rs.getString("descriere");
                    Utilizator utilizator = Utilizator.builder()
                            .username(pereche.getKey())
                            .medie(pereche.getValue())
                            .path_avatar(path_avatar)
                            .datan(datan)
                            .descriere(descriere)
                            .build();
                    list.add(utilizator);
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return list;
    }

    public void contextInitialized(ServletContextEvent event) {
        application = event.getServletContext();

        String dataBaseURL = application.getInitParameter("DataBaseURL");
        String dataBaseUser = application.getInitParameter("DataBaseUser");
        String dataBasePassword = application.getInitParameter("DataBasePassword");

        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection(dataBaseURL, dataBaseUser, dataBasePassword);
            application.setAttribute("conexiune", connection);
            System.err.println("Am deschis conexiunea la baza de date.");
        } catch (SQLException e) {
            System.err.println("Eroare la conectarea la baza de date");
        } catch (ClassNotFoundException e) {
            System.err.println("Driverul MySQL nu poate fi localizat");
        }
    }

    public void contextDestroyed(ServletContextEvent event) {
        ServletContext application = event.getServletContext();
        Connection con = (Connection) application.getAttribute("conexiune");
        try {
            con.close();
            System.err.println("Am inchis conexiunea la baza de date.");
        } catch (SQLException e) {
            System.err.println("Eroare la deconectarea de la baza de date");
        }
    }

    public static Utilizator autentificare(HttpSession session, String username, String password) {

        PreparedStatement preparedStatement = null;
        try {
            preparedStatement = connection.prepareStatement("SELECT password FROM utilizatori WHERE username=?");

            preparedStatement.setString(1, username);
            System.out.println(username);
            System.out.println(password);
            ResultSet rs = preparedStatement.executeQuery();

            if (rs.next() && rs.getString("password").equals(password)) {
                Utilizator utilizator = Utilizator.builder().password(password).username(username).build();
                session.setAttribute("utilizator", utilizator);
                return utilizator;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void addUser(String username, String password) {
        PreparedStatement preparedStatement;
        try {
            preparedStatement = connection.prepareStatement(
                    "INSERT INTO utilizatori(username, password) VALUES (?,?)");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            preparedStatement.execute();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}