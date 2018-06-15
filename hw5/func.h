#ifndef __FUNC_H__
#define __FUNC_H__

#include <map>
#include <iostream>

using std::map;
using std::ostream;

class func {
public:
    virtual ~func(){}
    func& operator<<(const int& x);
    virtual int apply(int) const = 0;
    virtual func* clone() const = 0;
    
protected:

    friend ostream& operator<<(ostream& os, const func& f);

    virtual void print(ostream& os) const = 0;

    int maxVal_; //maximum of all inputs
    int minVal_; //minimum of all inputs
    map<int, int> fmap_; //holds inputs and corresponding outputs
    void plot(ostream& os) const; //plot fmap_
};

ostream& operator<<(ostream&, const func&);

#endif
