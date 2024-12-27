#include <hello1.h>  // Підключаємо заголовковий файл із функцією print_hello()

MODULE_AUTHOR("Patsai Dmytro");
MODULE_DESCRIPTION("Lab5 Module hello2.c");
MODULE_LICENSE("Dual BSD/GPL");

// Оголошення параметра модуля
static uint parameter = 1;
// 0444 = S_IRUGO (тільки читання) - параметр доступний для читання через sysfs
module_param(parameter, uint, 0444);
MODULE_PARM_DESC(parameter, "My description");

// Функція ініціалізації модуля
static int __init hello2_init(void)
{
    pr_emerg("Calling print_hello() from hello2...\n");  // Лог повідомлення про виклик print_hello
    print_hello(parameter);  // Виклик функції print_hello() з параметром
    return 0;  // Успішна ініціалізація
}

// Функція завершення роботи модуля
static void __exit hello2_exit(void)
{
    // Порожня, оскільки завершення не потребує дій
}

module_init(hello2_init);
module_exit(hello2_exit);
