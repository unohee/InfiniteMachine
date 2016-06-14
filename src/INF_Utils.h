//
//  INF_Utils.h
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 14/06/2016.
//
//

#ifndef INF_Utils_h
#define INF_Utils_h

template<class T> class DeleteVector
{
public:
    // Overloaded () operator.
    // This will be called by for_each() function.
    bool operator()(T x) const
    {
        // Delete pointer.
        delete x;
        return true;
    }
};
class INF_Utils{
public:

};

#endif /* INF_Utils_h */
