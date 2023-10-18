typedef struct {
    int thread_id;
    int *cnt_ptr;
    pthread_mutex_t *mutex_ptr;
    pthread_mutex_t *print_ptr;
} ThreadInfo;

typedef struct {
    int			num_of_philosophers;
    int			time_to_deth;
    int			ime_to_eat;
    int			time_to_sleep;
    int			eat_count;
	mutex_info	mutex_status;
} philosopher_info;

typedef struct {
    int *fork;
    int pre_print;
    int print;
} mutex_info;

philo_info	*philosophers_and_mutex_struct_init(int argc, char *argv)
{
	philosophers_info philo_info;

	philo_info = (philo_info *) malloc (sizeof(philo_info) * 1);
	if (phino_info == NULL)
		exit (1);
	philo_info->num_of_philosophers =  argv[1];
    philo_info->time_to_deth = argv[2];
    philo_info->time_to_eat = argv[3];
    philo_info->time_to_sleep = argv[4];
	if (argc == 5)
		philo_info->eat_count = argv[5];
	
}

int	exec_philosopers(int argc, char *argv)
{
	philosophers_info	*philo_info;
//哲学者の初期化
	philo_info = philosophers_and_mutex_struct_init(argc, argv);

//mutexの初期化
	mutex_info = mutex_struct_init(phi);
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
