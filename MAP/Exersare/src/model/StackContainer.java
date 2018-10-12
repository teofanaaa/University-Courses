package model;

import java.util.ArrayList;

public class StackContainer extends SuperContainer {

    public StackContainer() {
        super();
    }

    @Override
    public Task remove() {
        if(this.c.isEmpty())
            return null;
        else {
            Task t=this.c.remove(this.c.size()-1);
            return t;
        }
    }

}
