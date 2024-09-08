#include<iostream>
#include<vector>
#include<time.h>


using namespace std;





//this Base class contains virtual functions
class Base {


    protected:
        float x1, y1;
        vector<float> elements;
        

    public:
        Base(float _x1, float _y1, int _n, float* _v) : x1(_x1), y1(_y1) {
            for(int i = 0; i < _n; i++){
                elements.push_back(_v[i]);
            }
        }
        
        //a small virtual function call
        virtual float small() = 0;

        // a bigger function see in the implementation in subclasses  
        virtual float big() = 0;


};

//the first subclass of Base
class Virtual1 : public Base{

    public:
        Virtual1(float x, float y, int n, float *v) : Base(x,y,n,v) {}

        float small() override { return x1 * y1;}

        float big() override {

            float sum = 0;
            for(auto i : elements){
                sum += i;
            }


            return sum;
        }

};

//the second subclass of Base
class Virtual2 : public Base{

    public:
    
        Virtual2(float x, float y, int n, float *v) : Base(x,y,n,v) {}

        float small() override { return x1 + y1;}

        // we want to test both case, if allow and forbid the compiler to inline
        #ifdef NOINLINE
        __attribute__ ((noinline)) 
        #endif
        float big() override {

            float sum = 0;
            for(auto i : elements){
                sum += i + 1;
            }

            
            return sum;
        }

};


//this Base2 class does not contain virtual function, but implements the same functionality as Virtual2 class
class Base2 {


    protected:
        float x1, y1;
        vector<float> elements;
        

    public:
        Base2(float _x1, float _y1, int _n, float* _v) : x1(_x1), y1(_y1) {
            for(int i = 0; i < _n; i++){
                elements.push_back(_v[i]);
            }
        }
        

        float small()  { return x1 + y1;}

         // we want to test both case, if allow and forbid the compiler to inline
        #ifdef NOINLINE
        __attribute__ ((noinline)) 
        #endif
        float big()  {

            float sum = 0;
            for(auto i : elements){
                sum += i + 1;
            }

            
            return sum;
        }


};






int main(){

    int n = 1000000000;

    time_t begin, end;
    double spent;


    
    //initialize objects with and without virtual functions

    float w[10] = {1.3, 1.4, 1.5, 1.3, 1.4, 1.5, 1.3, 1.4, 1.5, 9.1};
    Base* Virtual = new Virtual2(1.0, 1.2, 10, w);
    Base2* NotVirtual = new Base2(1.0, 1.2, 10, w);

    float res;


    //time measurement, sorry for code duplication

    begin = clock();

    for(int i = 0; i < n; i++){
        res = Virtual->small();
    }

    end = clock();
    spent = (double)(end - begin)/CLOCKS_PER_SEC;
    
    std :: cout << "result small virtual function: " << res << "     || time spent: " << spent << std::endl;


    begin = clock();

    for(int i = 0; i < n; i++){
        res = NotVirtual->small();
    }

    end = clock();
    spent = (double)(end - begin)/CLOCKS_PER_SEC;
    
    std :: cout << "result small not virtual function: " << res << " || time spent: " << spent << std::endl;





    begin = clock();

    for(int i = 0; i < n; i++){
        res = Virtual->big();
    }

    end = clock();
    spent = (double)(end - begin)/CLOCKS_PER_SEC;

    #ifdef NOINLINE

    std :: cout <<  "inline is not allowed" << std::endl;

    #else
    std :: cout <<  "inline is not allowed" << std::endl;

    #endif
    
    std :: cout << "result big virtual function: " << res << "      || time spent: " << spent << std::endl;




    begin = clock();

    for(int i = 0; i < n; i++){
        res = NotVirtual->big();
    }

    end = clock();
    spent = (double)(end - begin)/CLOCKS_PER_SEC;
    
    std :: cout << "result big not virtual function: " << res << "  || time spent: " << spent << std::endl;


    return 0;

}