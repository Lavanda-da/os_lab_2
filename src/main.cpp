#include <iostream>
#include <pthread.h>
#include <time.h>
#include <vector>

std::string str, pattern;
int step;
std::vector<int> res;

struct pthread_args {
    int begin;
    int end;
};

void* Naive_search(void* arg) {
    struct pthread_args* args = ((struct pthread_args*) arg);
    int begin = args->begin;
    int end = args->end;
    for (int i = begin; i < end; ++i)
    {
        bool flag = true;
        for (int j = 0; j < pattern.size(); ++j) {
            if (i + j >= str.size()) {
                break;
            }
            if (str[i + j] != str[j]) {
                flag = false;
            }
        }
        if (flag) {
            res.push_back(i);
        }
    }
    pthread_exit(0);
    return 0;
}

int main(int argc, char* argv[]) {
    int count_pthreads = 0;
    for (int i = 0; i < static_cast <std::string> (argv[1]).size(); ++i) {
        count_pthreads *= 10;
        count_pthreads += (argv[1][i] - '0');
    }
    std::cin >> str >> pattern;
    step = (str.size()) / count_pthreads;

    pthread_t tid[count_pthreads];
    struct pthread_args *args_pth = (struct pthread_args*) malloc (count_pthreads * sizeof(struct pthread_args));

    for (int i = 0; i < count_pthreads; ++i) {
        if (i == count_pthreads - 1) {
            args_pth[i].begin = i * step;
            args_pth[i].end = str.size();
        } else {
            args_pth[i].begin = i * step;
            args_pth[i].end = (i + 1) * step;
        }
    }

    struct timespec start, stop;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < count_pthreads; ++i) {
        pthread_create(&tid[i], NULL, Naive_search, (void*)&args_pth[i]);
    }

    for (int i = 0; i < count_pthreads; ++i)
    {
        pthread_join(tid[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &stop);
    long long elapsed_time = (stop.tv_sec - start.tv_sec) * 1000000000 + (stop.tv_nsec - start.tv_nsec);
    std::cout << count_pthreads << ' ' << elapsed_time << std::endl;

    // for (int i = 0; i < res.size(); ++i) {
    //     std::cout << res[i] << ' ';
    // }
    // std::cout << std::endl;
    return 0;
}