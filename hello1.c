#include <hello1.h>

MODULE_AUTHOR("Patsai Dmytro");
MODULE_DESCRIPTION("Lab5 Module hello1.c");
MODULE_LICENSE("Dual BSD/GPL");

// Структура для збереження часу виконання та зв'язку в списку
struct myStruct {
    struct list_head list;  // Зв'язок зі списком
    ktime_t startTime;      // Час початку
    ktime_t finishTime;     // Час завершення
};

// Статична зміна для голови списку
static LIST_HEAD(myList);
int counter;

// Функція для друку привітання
int print_hello(uint parameter)
{
    BUG_ON(parameter > 10);

    // Попередження для певних значень параметра
    if (parameter == 0 || (parameter <= 10 && parameter >= 5)) {
        pr_emerg("Warning: %u\n", parameter);
    }

    // Ініціалізація лічильника
    counter = 0;
    while (counter != parameter) {
        // Виділення пам'яті для нового елементу списку
        struct myStruct *ptr = kmalloc(sizeof(*ptr), GFP_KERNEL); 
        if (!ptr) {
            pr_err("Memory allocation failed\n");
            return -ENOMEM;
        }
	ptr = 0;
        // Запис часу початку виконання
        ptr->startTime = ktime_get();
        pr_emerg("Hello world!\n");

        // Запис часу завершення виконання
        ptr->finishTime = ktime_get();

        // Додавання нового елементу до кінця списку
        list_add_tail(&ptr->list, &myList);
        counter += 1;
    }
    return 0;
}
EXPORT_SYMBOL(print_hello);

// Ініціалізація модуля
static int __init hello1_init(void)
{
    return 0; // Повертаємо 0, якщо ініціалізація успішна
}

// Завершення роботи модуля
static void __exit hello1_exit(void)
{
    struct myStruct *ptr, *next;

    // Безпечне проходження списку для очищення елементів
    list_for_each_entry_safe(ptr, next, &myList, list) {
        // Виведення часу виконання у наносекундах
        pr_emerg("Time in nanoseconds: %lld\n", ptr->finishTime - ptr->startTime);

        // Видалення елементу зі списку
        list_del(&ptr->list);

        // Звільнення пам'яті, виділеної для елементу
        kfree(ptr);
    }
}

module_init(hello1_init);
module_exit(hello1_exit);
