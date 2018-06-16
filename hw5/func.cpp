#include "func.h"
#include <vector>
#include <algorithm>

using namespace std;

func::func() :
    maxVal_(INT32_MIN),
    minVal_(INT32_MAX)
{
}

func& func::operator<<(const int& x)
{
    if (fmap_.empty())
    {
        minVal_ = x;
        maxVal_ = x;
    }
    else if(x < minVal_)
    {
        minVal_ = x;
    }
    else if (x > maxVal_)
    {
        maxVal_ = x;
    }

    fmap_[x] = apply(x);    
    
    return *this;
}

ostream& operator<<(ostream& os, const func& f)
{
    f.print(os);
    if(!f.fmap_.empty())
    {
        f.plot(os);
    }

    return os;
}

void func::plot(ostream& os) const
{
    vector<int> sortImage;

    sortImage.clear();
    for (map<int, int>::const_iterator it = fmap_.begin();
        it != fmap_.end(); ++it)
    {
        sortImage.push_back(it->second);
    }
    sort(sortImage.begin(), sortImage.end());
    reverse(sortImage.begin(), sortImage.end());

    for (vector<int>::iterator it_im = sortImage.begin();
        it_im != sortImage.end(); ++it_im)
    {
        if (it_im != sortImage.begin() && *it_im == *(it_im - 1))
        {
            //remove repeated
            it_im = sortImage.erase(it_im) - 1;
        }
    }
    //Now  sortImage holds all the outputs in fmap_ sorted reversed and unique

    for (vector<int>::iterator it_im = sortImage.begin();
        it_im != sortImage.end(); ++it_im)
    {
        int x_anchor = minVal_;
        // print y axis
        if (*it_im < -9)
            os << *it_im;
        else if ((*it_im < 0) || (*it_im > 9))
            os << " " << *it_im;
        else
            os << "  " << *it_im;

        for (map<int, int>::const_iterator it_dom = fmap_.begin();
            it_dom != fmap_.end(); ++it_dom)
        {
            //print (x,y)
            if (it_dom->second == *it_im)
            {
                int x = it_dom->first;
                int spaces = x - x_anchor;
                int i = 0;
                while (i < spaces)
                {
                    os << "   ";
                    i++;
                }
                os << "*  ";
                x_anchor = x + 1;
            }
        }// for fmap_

        os << endl;
        if ((it_im + 1) != sortImage.end())
        {
            //print empty lines
            int lines = *it_im - *(it_im + 1) - 1;
            int i = 1;

            while (i < lines + 1)
            {
                if (*it_im - i < -9)
                    os << *it_im - i;
                else if ((*it_im - i < 0) || (*it_im - i > 9))
                    os << " " << *it_im - i;
                else
                    os << "  " << *it_im - i;
                cout << endl;
                i++;
            }
        }
    }//for sortImage
    //print x axis
    cout << " ";
    for (int i = minVal_; i < maxVal_ + 1; i++)
    {
        if (i < 0) os << " " << i;
        else os << "  " << i;
    }
    os << endl;
}
