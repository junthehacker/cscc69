/**
 * This illustrates how race condition can happen if you don't use locks
 * Here we have 2 threads withdrawing money from the account
 * however withdrawing takes 1 second to process, resulting overdraft.
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

bool lock = false;
int account_balance = 0;

void acquire(bool *lock) {
    while(*lock); // Keep waiting for lock
    *lock = true; // Lock released, acquire
}

void release(bool *lock) {
    *lock = false;
}

void *deposit(void *vargp) {
    acquire(&lock);
    account_balance += 100;
    printf("Deposit successful, balance: %d\n", account_balance);
    release(&lock);
    return NULL;
}

void *withdrawal(void *vargp) {
    sleep(1);
    acquire(&lock);
    // We can only withdraw if balance is greater or equal to 100
    if(account_balance >= 100) {
        sleep(1); // Say somehow withdraw money takes 1 sec
        account_balance -= 100;
        printf("Withdraw successful, balance: %d\n", account_balance);
    } else {
        printf("Failed to withdraw, balance not sufficient: %d\n", account_balance);
    }
    release(&lock);
    return NULL;
}


int main() {
    pthread_t deposit_id, withdrawal_id, withdrawal_id_2;
    pthread_create(&deposit_id, NULL, deposit, NULL);
    pthread_create(&withdrawal_id, NULL, withdrawal, NULL);
    pthread_create(&withdrawal_id_2, NULL, withdrawal, NULL);
    
    pthread_join(deposit_id, NULL);
    pthread_join(withdrawal_id, NULL);
    pthread_join(withdrawal_id_2, NULL);

    printf("Current account balance is %d\n", account_balance);

    return 0;
}