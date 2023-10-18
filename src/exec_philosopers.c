typedef struct {
    int thread_id;
    int *cnt_ptr;
    pthread_mutex_t *mutex_ptr;
    pthread_mutex_t *print_ptr;
} ThreadInfo;

typedef struct {
    int num_of_philosophers;
    int time_to_deth;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
} philosopher_info;

typedef struct {
    int num_of_philosophers;
    int time_to_deth;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
} mutex_info;

int	exec_philosopers(int argc, char *argv)
{
	philosophers_info philo_info;
//哲学者の初期化
	philo_info = philosophers_init(argc, argv);

//mutexの初期化
	mutex_init();
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&print, NULL);

//threadの初期化
    ThreadInfo info1 = {1, &cnt, &mutex, &print};
    ThreadInfo info2 = {2, &cnt, &mutex, &print};

//threadの作成
    pthread_create(&p1, NULL, routine, (void *)&info1);
    pthread_create(&p2, NULL, routine, (void *)&info2);

//他のthreadを待つ
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

//mutexの破壊
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&print);

//値の表示
    printf("Final cnt -> %d\n", cnt);

    return 0;
	(void)argc;
	(void)argv;

}
