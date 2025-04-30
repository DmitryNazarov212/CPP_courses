#include <random>

class ArrayCreator
{
    public:
        ArrayCreator()
        {
            r_gen.seed(r_dev());
        }
        ~ArrayCreator()
        {
            if(arr) delete[] arr;
        }
        int* createArray(size_t size)
        {
            arr = new int[size];
            for (int i = 0; i < size; ++i) 
            {
                arr[i] = getNum();
            }
            return arr;
        }
    private:
        int getNum()
        {
            std::uniform_int_distribution<int> range(0, 800);
            return range(r_gen);
        }
        std::random_device r_dev;
        std::mt19937 r_gen;
        int* arr;
};