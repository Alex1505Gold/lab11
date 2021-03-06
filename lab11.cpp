﻿#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>

void find_max(std::vector<int>& v, int& m, int k, int beg, int end)
{
    m = -1;
    for (unsigned int i = beg; i < end; ++i)
    {
        if (v[i] > m) m = v[i];
    }
    if (k != 0)
    {
        std::cout << "Max value: " << m << " in thread " << k << std::endl;
    }
    else
    {
        std::cout << "Final max value: " << m << std::endl;
    }
}

int main()
{
    std::srand(55);
    std::vector<int> vec0;
    int m = -1;
    for ( long long int i = 0; i < 12600000; ++i)
    {
        vec0.push_back(rand());
        //std::cout << vec0[i] << " ";
    }
    //std::cout << find_max(vec0);
    /*std::cout << "One thread" << std::endl;
    
    std::thread* t;
    
    t = new std::thread(find_max, std::ref(vec0), std::ref(m), 1);
    //std::cout << t.get_id() << std::endl;
    
    t->join();
    std::cout << "Final max value: " << m << std::endl;
    delete t;
    
    
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;*/
    auto start = std::chrono::steady_clock::now();
    auto stop = std::chrono::steady_clock::now();
    std::vector<int> max;
    for (int i = 0; i < 8; ++i)
    {
        max.push_back(-1);
    }
    
    //std::vector<std::vector<int>> vecs; 
    
    int begin, end, step;
    std::vector<int> cur_vec;
    for (int j = 1; j <= 8; ++j)
    {

        int count_of_threads = j;
        std::thread* ts[8]; //тк у меня на компьютере 8 логических процессоров
        std::cout << count_of_threads << " threads" << std::endl;
        step = vec0.size() / j;
        begin = 0;
        end = step;
        /*
        for (int i = 0; i < count_of_threads; ++i)
        {
            for (long long int k = begin; k < end; ++k)
            {
                cur_vec.push_back(vec0[k]);
            }
            vecs.push_back(cur_vec);
            begin += step;
            end += step;
            cur_vec.clear();
        }
        */
        start = std::chrono::steady_clock::now();
        for (int i = 0; i < count_of_threads; ++i)
        {

            ts[i] = new std::thread(find_max, std::ref(vec0), std::ref(max[i]), i + 1, begin, end);

            begin += step;
            end += step;
        }
        for (int i = 0; i < count_of_threads; ++i)
        {
            ts[i]->join();
            delete ts[i];
        }
        find_max(max, m, 0, 0, max.size());
        stop = std::chrono::steady_clock::now();
        std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
        for (int i = 0; i < j; ++i)
        {
            max[i] = -1;
        }
        //vecs.clear();
    }
    //исполбзование многопоточностти позволило уменьшить время выполнения работы с 1млн мксек до 200тыс, т.е. в 5 раз
    return 0;
}


