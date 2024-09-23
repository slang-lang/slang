#!/usr/local/bin/oscript

import System.Thread;


public object MyThread extends Thread {
    public void Constructor(string name) {
        base.Constructor(name);
    }

    public void start() {
        print("Customized start method");
    }

    public void run() {
        print(getName() + ": running my own thread");

        int count;
        while ( count < 1000 ) {
            sleep(1);

            count++;
        }
    }
}

public void Main(int argc, string args) {
    MyThread thread1 = new MyThread("Thread1");
    MyThread thread2 = new MyThread("Thread2");
}
