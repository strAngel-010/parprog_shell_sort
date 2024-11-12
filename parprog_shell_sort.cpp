#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

double count_time(std::vector<int>& array, const int threads);

int main() {
    const int count = 60000000;
    const int random_seed = 920214;
    const int threads = omp_get_num_procs();
    srand(random_seed);
    
    std::vector<int> array(count);
    for (int j = 0; j < count; j++) { 
        array[j] = rand(); 
    }
    
    double res_time = count_time(array, threads);
    std::cout << "Threads: " << threads << 
        ", Time: " << res_time << " seconds" << std::endl;

    return 0;
}

double count_time(std::vector<int>& array, const int threads) {
    int tmp, cur_ind;

    double start = omp_get_wtime();
    
    for (int s = array.size() / 2; s != 0; s /= 2) {
        #pragma omp parallel for num_threads(threads) shared(array, s) private(tmp, cur_ind)
        for (int i = 0; i < s; i++) {
            for (int j = i + s; j < array.size(); j += s) {
                tmp = array[j];
                cur_ind = j - s;
                
                while (cur_ind >= i && array[cur_ind] > tmp) {
                    array[cur_ind + s] = array[cur_ind];
                    cur_ind -= s;
                }
                
                array[cur_ind + s] = tmp;
            }
        }
    }
    
    double end = omp_get_wtime();
    return end-start;
}
