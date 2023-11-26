#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Cell;

class Observer {
    public:
        virtual void notify(Cell &c) = 0; // c is the Cell that called notify method
        virtual ~Observer() = default;
};

#endif
