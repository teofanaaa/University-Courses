﻿
namespace OpenTKTutorial6
{
    class Program
    {
        static void Main(string[] args)
        {
            using (Game game = new Game())
            {

                game.Run(30, 30);

            }
        }
    }
}
