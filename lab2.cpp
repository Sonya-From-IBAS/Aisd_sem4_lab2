#include <iostream>
#include <vector>
#include <chrono>

//a function that generates pseudo-random numbers to fill an array.
size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

//stats class with added sorting time value.
struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
    size_t sortTime = 0;
};

//inserts sorting.Two iterators are usedand the time is being counted.
stats insertSort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    stats resultStat;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for (std::vector<int>::iterator i = begin + 1; i < end; ++i)
    {
        resultStat.comparison_count += 1;
        for (std::vector<int>::iterator j = i; j > begin && *(j - 1) > *j; --j)
        {
            resultStat.comparison_count += 1;
            resultStat.copy_count += 3;
            std::swap(*j, *(j - 1));
        }

    }
    std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    resultStat.sortTime = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    return resultStat;
}

//shaker sorting. Two iterators are used and the time is being counted
stats shakerSort(std::vector<int>::iterator begin, std::vector<int>::iterator end) { //T = std::vector<type>::iterator
    stats resultStat;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::vector<int>::iterator left = begin;
    std::vector<int>::iterator right = end - 1;
    while (left < right) {

        for (std::vector<int>::iterator i = left; i < right; ++i)
        {
            resultStat.comparison_count += 1;
            if (*i > *(i + 1)) {
                std::swap(*i, *(i + 1));
                resultStat.copy_count += 3;
            }
        }
        --right;

        for (std::vector<int>::iterator j = right; j > left; --j) {
            resultStat.comparison_count += 1;
            if (*j < *(j - 1)) {
                std::swap(*j, *(j - 1));
                resultStat.copy_count += 3;
            }
        }
        ++left;
    }
    std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    resultStat.sortTime = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    return resultStat;
}

//additional sorting with a comb from the third group.Two iterators are usedand time is being counted
stats combSort(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::vector<int>& vect) {
    stats resultStat;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    double factor = 1.24773309;
    int step = vect.size() - 1;
    while (step >= 1) {
        for (std::vector<int>::iterator i = begin; i + step < end; ++i)
        {
            if (*i > *(i + step)) {
                std::swap(*i, *(i + step));
                resultStat.copy_count += 3;
            }
            resultStat.comparison_count += 1;
        }
        step /= factor;
    }
    std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    resultStat.sortTime = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    return resultStat;
}

stats onAverageInsertSort(size_t vectLenght) {
    stats resultStat;
    for (size_t i = 0; i < 100; i++)
    {
        std::vector<int> vect;
        for (size_t j = 0; j < vectLenght; j++)
        {
            vect.push_back(lcg());
        }
        stats currentStat = insertSort(vect.begin(), vect.end());

        resultStat.comparison_count += currentStat.comparison_count;
        resultStat.copy_count += currentStat.copy_count;
        resultStat.sortTime += currentStat.sortTime;
    }
    std::cout << "onAverageInsertSort:\nvectLenght - " << vectLenght << " numbers,\ntime -  " << resultStat.sortTime / 100 << " microseconds,\ncomparison count - " << resultStat.comparison_count / 100 << " times,\ncopy count - " << resultStat.copy_count / 100 << " times\n" << std::endl;
    return resultStat;
}
stats onAverageShakerSort(size_t vectLenght) {
    stats resultStat;
    for (size_t i = 0; i < 100; i++)
    {
        std::vector<int> vect;
        for (size_t j = 0; j < vectLenght; j++)
        {
            vect.push_back(lcg());
        }
        stats currentStat = shakerSort(vect.begin(), vect.end());

        resultStat.comparison_count += currentStat.comparison_count;
        resultStat.copy_count += currentStat.copy_count;
        resultStat.sortTime += currentStat.sortTime;
    }
    std::cout << "onAverageShakerSort:\nvectLenght - " << vectLenght << " numbers,\ntime -  " << resultStat.sortTime / 100 << " microseconds,\ncomparison count - " << resultStat.comparison_count / 100 << " times,\ncopy count - " << resultStat.copy_count / 100 << " times\n" << std::endl;
    return resultStat;
}
stats onAverageCombSort(size_t vectLenght) {
    stats resultStat;
    for (size_t i = 0; i < 100; i++)
    {
        std::vector<int> vect;
        for (size_t j = 0; j < vectLenght; j++)
        {
            vect.push_back(lcg());
        }
        stats currentStat = combSort(vect.begin(), vect.end(), vect);

        resultStat.comparison_count += currentStat.comparison_count;
        resultStat.copy_count += currentStat.copy_count;
        resultStat.sortTime += currentStat.sortTime;
    }
    std::cout << "onAverageCombSort:\nvectLenght - " << vectLenght << " numbers,\ntime -  " << resultStat.sortTime / 100 << " microseconds,\ncomparison count - " << resultStat.comparison_count / 100 << " times,\ncopy count - " << resultStat.copy_count / 100 << " times\n" << std::endl;
    return resultStat;
}

stats onSortedInsertSort(size_t vectLenght){
    stats resultStat;
    std::vector<int> vect;
    for (size_t i = 0; i < vectLenght; i++)
    {
        vect.push_back(i);
    }
    stats currentStat = insertSort(vect.begin(), vect.end());

    resultStat.comparison_count += currentStat.comparison_count;
    resultStat.copy_count += currentStat.copy_count;
    resultStat.sortTime += currentStat.sortTime;
    std::cout << "onSortedInsertSort:\nvectLenght - " << vectLenght;
    std::cout << " numbers,\ntime -  " << resultStat.sortTime;
    std::cout  << " microseconds,\ncomparison count - " << resultStat.comparison_count;
    std::cout  << " times,\ncopy count - " << resultStat.copy_count<< " times\n" << std::endl;
    return resultStat;
}
stats onSortedShakerSort(size_t vectLenght){
    stats resultStat;
    std::vector<int> vect;
    for (size_t i = 0; i < vectLenght; i++)
    {
        vect.push_back(i);
    }
    stats currentStat = shakerSort(vect.begin(), vect.end());

    resultStat.comparison_count += currentStat.comparison_count;
    resultStat.copy_count += currentStat.copy_count;
    resultStat.sortTime += currentStat.sortTime;
    std::cout << "onSortedShakerSort:\nvectLenght - " << vectLenght;
    std::cout << " numbers,\ntime -  " << resultStat.sortTime;
    std::cout << " microseconds,\ncomparison count - " << resultStat.comparison_count;
    std::cout << " times,\ncopy count - " << resultStat.copy_count<< " times\n" << std::endl;
    return resultStat;
}
stats onSortedCombSort(size_t vectLenght){
    stats resultStat;
    std::vector<int> vect;
    for (size_t i = 0; i < vectLenght; i++)
    {
        vect.push_back(i);
    }
    stats currentStat = combSort(vect.begin(), vect.end(), vect);

    resultStat.comparison_count += currentStat.comparison_count;
    resultStat.copy_count += currentStat.copy_count;
    resultStat.sortTime += currentStat.sortTime;
    std::cout << "onSortedCombSort:\nvectLenght - " << vectLenght;
    std::cout << " numbers,\ntime -  " << resultStat.sortTime;
    std::cout << " microseconds,\ncomparison count - " << resultStat.comparison_count;
    std::cout << " times,\ncopy count - " << resultStat.copy_count<< " times\n" << std::endl;
    return resultStat;
}

stats onReversedSortedInsertSort(size_t vectLenght) {
    stats resultStat;
    std::vector<int> vect;
    for (size_t i = vectLenght; i > 0; i--)
    {
        vect.push_back(i);
    }
    stats currentStat = insertSort(vect.begin(), vect.end());

    resultStat.comparison_count += currentStat.comparison_count;
    resultStat.copy_count += currentStat.copy_count;
    resultStat.sortTime += currentStat.sortTime;
    std::cout << "onReversedSortedInsertSort:\nvectLenght - " << vectLenght;
    std::cout << " numbers,\ntime -  " << resultStat.sortTime;
    std::cout << " microseconds,\ncomparison count - " << resultStat.comparison_count;
    std::cout << " times,\ncopy count - " << resultStat.copy_count << " times\n" << std::endl;
    return resultStat;
}
stats onReversedSortedShakerSort(size_t vectLenght) {
    stats resultStat;
    std::vector<int> vect;
    for (size_t i = vectLenght; i > 0; i--)
    {
        vect.push_back(i);
    }
    stats currentStat = shakerSort(vect.begin(), vect.end());

    resultStat.comparison_count += currentStat.comparison_count;
    resultStat.copy_count += currentStat.copy_count;
    resultStat.sortTime += currentStat.sortTime;
    std::cout << "onReversedSortedShakerSort:\nvectLenght - " << vectLenght;
    std::cout << " numbers,\ntime -  " << resultStat.sortTime;
    std::cout << " microseconds,\ncomparison count - " << resultStat.comparison_count;
    std::cout << " times,\ncopy count - " << resultStat.copy_count << " times\n" << std::endl;
    return resultStat;
}
stats onReversedSortedCombSort(size_t vectLenght) {
    stats resultStat;
    std::vector<int> vect;
    for (size_t i = vectLenght; i > 0; i--)
    {
        vect.push_back(i);
    }
    stats currentStat = combSort(vect.begin(), vect.end(), vect);

    resultStat.comparison_count += currentStat.comparison_count;
    resultStat.copy_count += currentStat.copy_count;
    resultStat.sortTime += currentStat.sortTime;
    std::cout << "onReversedSortedCombSort:\nvectLenght - " << vectLenght;
    std::cout << " numbers,\ntime -  " << resultStat.sortTime;
    std::cout << " microseconds,\ncomparison count - " << resultStat.comparison_count;
    std::cout << " times,\ncopy count - " << resultStat.copy_count << " times\n" << std::endl;
    return resultStat;
}

int main()
{
    bool programm_runner = true;
    size_t programmAction;
    while (programm_runner) {
        std::cout << "User interface for working with sort algorithms" << std::endl;
        std::cout << "1) Check the operation of sorting algorithms." << std::endl;
        std::cout << "2) Check the operation of the algorithms according to the task." << std::endl;
        std::cout << "3) Exit programm." << std::endl;
        std::cin >> programmAction;

        switch (programmAction)
        {
        case 1:
        {
            system("cls");
            size_t sortingType;
            std::cout << "You have selected the checking the operation of sorting algorithms." << std::endl;
            std::cout << "Choose which sort you want to apply:" << std::endl;
            std::cout << "1) Insert sort." << std::endl;
            std::cout << "2) Shaker sort." << std::endl;
            std::cout << "3) Comb sort." << std::endl;
            std::cout << "4) Exit." << std::endl;
            std::cin >> sortingType;
            switch (sortingType)
            {
            case 1:
            {
                system("cls");
                size_t vectLenght;
                std::vector<int> vect;
                std::cout << "You have selected insert sort." << std::endl;
                std::cout << "Enter the size of the array you want to sort:" << std::endl;
                std::cin >> vectLenght;
                for (size_t i = 0; i < vectLenght; i++)
                {
                    int number;
                    std::cout << "\nEnter " << i << "number of array:";
                    std::cin >> number;
                    vect.push_back(number);
                }
                std::cout << "\nYour array is:" << std::endl;
                for (auto i : vect) {
                    std::cout << i << " ";
                }
                stats curStat = insertSort(vect.begin(), vect.end());
                std::cout << "\nSorted array:" << std::endl;
                for (auto i : vect) {
                    std::cout << i << " ";
                }
                std::cout << "\ntime -  " << curStat.sortTime;
                std::cout << " microseconds,\ncomparison count - " << curStat.comparison_count;
                std::cout << " times,\ncopy count - " << curStat.copy_count << " times\n" << std::endl;
                break;
            }
            case 2:
            {
                system("cls");
                size_t vectLenght;
                std::vector<int> vect;
                std::cout << "You have selected shaker sort." << std::endl;
                std::cout << "Enter the size of the array you want to sort:" << std::endl;
                std::cin >> vectLenght;
                for (size_t i = 0; i < vectLenght; i++)
                {
                    int number;
                    std::cout << "\nEnter " << i << "number of array:";
                    std::cin >> number;
                    vect.push_back(number);
                }
                std::cout << "\nYour array is:" << std::endl;
                for (auto i : vect) {
                    std::cout << i << " ";
                }
                stats curStat = shakerSort(vect.begin(), vect.end());
                std::cout << "\nSorted array:" << std::endl;
                for (auto i : vect) {
                    std::cout << i << " ";
                }
                std::cout << "\ntime -  " << curStat.sortTime;
                std::cout << " microseconds,\ncomparison count - " << curStat.comparison_count;
                std::cout << " times,\ncopy count - " << curStat.copy_count << " times\n" << std::endl;
                break;
            }
            case 3:
            {
                system("cls");
                size_t vectLenght;
                std::vector<int> vect;
                std::cout << "You have selected comb sort." << std::endl;
                std::cout << "Enter the size of the array you want to sort:" << std::endl;
                std::cin >> vectLenght;
                for (size_t i = 0; i < vectLenght; i++)
                {
                    int number;
                    std::cout << "\nEnter " << i << "number of array:";
                    std::cin >> number;
                    vect.push_back(number);
                }
                std::cout << "\nYour array is:" << std::endl;
                for (auto i : vect) {
                    std::cout << i << " ";
                }
                stats curStat = combSort(vect.begin(), vect.end(), vect);
                std::cout << "\nSorted array:" << std::endl;
                for (auto i : vect) {
                    std::cout << i << " ";
                }
                std::cout << "\ntime -  " << curStat.sortTime;
                std::cout << " microseconds,\ncomparison count - " << curStat.comparison_count;
                std::cout << " times,\ncopy count - " << curStat.copy_count << " times\n" << std::endl;
                break;
            }
            case 4:
            {
                system("cls");
                std::cout << "You will be moved to the main menu." << std::endl;
            }
            default:
            {
                system("cls");
                std::cout << "You have selected non - existent option, try it again." << std::endl;
                break; 
            }
            }
            break;
        }
        case 2:
        {
            system("cls");
            std::cout << "You have selected the checking the operation of the algorithms according to the task.." << std::endl;
            std::vector<int>vect;
            vect.push_back(1000);
            vect.push_back(2000);
            vect.push_back(3000);
            vect.push_back(4000);
            vect.push_back(5000);
            vect.push_back(6000);
            vect.push_back(7000);
            vect.push_back(8000);
            vect.push_back(9000);
            vect.push_back(10000);
            vect.push_back(25000);
            vect.push_back(50000);
            vect.push_back(100000);

            std::cout << "\n\n\n" << std::endl;
            std::cout << "AVERAGE SORT" << std::endl;
            for (auto i : vect) {
                onAverageInsertSort(i);
            }
            std::cout << "\n\n\n" << std::endl;
            for (auto i : vect) {
                onAverageShakerSort(i);
            }
            std::cout << "\n\n\n" << std::endl;
            for (auto i : vect) {
                onAverageCombSort(i);
            }

            /*std::cout << "\n\n\n" << std::endl;
            std::cout << "SORTED SORT" << std::endl;
            for (auto i : vect) {
                onSortedInsertSort(i);
            }
            std::cout << "\n\n\n" << std::endl;
            for (auto i : vect) {
                onSortedShakerSort(i);
            }
            std::cout << "\n\n\n" << std::endl;
            for (auto i : vect) {
                onSortedCombSort(i);
            }

            std::cout << "\n\n\n" << std::endl;
            std::cout << "REVERSE SORTED SORT" << std::endl;
            for (auto i : vect) {
                onReversedSortedInsertSort(i);
            }
            std::cout << "\n\n\n" << std::endl;
            for (auto i : vect) {
                onReversedSortedShakerSort(i);
            }
            std::cout << "\n\n\n" << std::endl;
            for (auto i : vect) {
                onReversedSortedCombSort(i);
            }*/


            break;
        }
        
        case 3:
        {
            programm_runner = false;
            system("cls");
            std::cout << "You have exited the program." << std::endl;
            break;
        }
        default:
        {
            system("cls");
            std::cout << "You have selected non - existent option, try it again." << std::endl;
            break;
        }
        }
        system("pause");
        system("cls");
    }
}


















/*std::vector<int> vect;
    for (size_t i = 0; i < 40; i++)
    {
        vect.push_back(lcg());
    }
    vect.push_back(7);
    vect.push_back(0);
    vect.push_back(-4);
    vect.push_back(3);
    vect.push_back(1);
    vect.push_back(-2);
    vect.push_back(5);
    std::vector<int>::iterator it1 = vect.begin();
    std::vector<int>::iterator it2 = vect.end();
    if(it2>it1){
        std::cout << "it2>it1";
    }
    for (auto i : vect) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    combSort(vect.begin(), vect.end(), vect);
    for (auto i : vect) {
        std::cout << i << " ";
    }
    insertSort(vect.begin(), vect.end());
    for (auto i : vect) {
        std::cout << i << " ";
    }

    std::cout << "Hello World!\n";*/