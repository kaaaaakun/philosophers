typedef struct {
    int thread_id;
    int *cnt_ptr;
    pthread_mutex_t *mutex_ptr;
    pthread_mutex_t *print_ptr;
} ThreadInfo;

void *routine(void *arg)
{
    ThreadInfo *info = (ThreadInfo *)arg;

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(info->mutex_ptr);
        (*(info->cnt_ptr))++;
        pthread_mutex_unlock(info->mutex_ptr);

        pthread_mutex_lock(info->print_ptr);
        printf("Thread %d incremented cnt to %d\n", info->thread_id, *(info->cnt_ptr));
        pthread_mutex_unlock(info->print_ptr);
    }
    return NULL;
}

int main(int argc, char *argv)
{
    pthread_t p2;
    pthread_t p1;
    pthread_mutex_t mutex;
    pthread_mutex_t print;
    int cnt = 0;

//引数のチェック
	if (args_error_check(argc, argv) == -1)
		exit (1);

	exec_philosopers(argc, argv);
	exit();
////mutexの初期化
//    pthread_mutex_init(&mutex, NULL);
//    pthread_mutex_init(&print, NULL);
//
////threadの初期化
//    ThreadInfo info1 = {1, &cnt, &mutex, &print};
//    ThreadInfo info2 = {2, &cnt, &mutex, &print};
//
////threadの作成
//    pthread_create(&p1, NULL, routine, (void *)&info1);
//    pthread_create(&p2, NULL, routine, (void *)&info2);
//
////他のthreadを待つ
//    pthread_join(p1, NULL);
//    pthread_join(p2, NULL);
//
////mutexの破壊
//    pthread_mutex_destroy(&mutex);
//    pthread_mutex_destroy(&print);
//
////値の表示
//    printf("Final cnt -> %d\n", cnt);

    return 0;
	(void)argc;
	(void)argv;

}
