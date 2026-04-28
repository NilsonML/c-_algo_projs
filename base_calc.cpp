#include <iostream>
#include <cstring>
#include <menu.h>    // Библиотека для создания меню
#include <curses.h>  // Библиотека управления терминалом
using namespace std;

int main() {
    // INSTRUCTION: Use UP/DOWN arrows to navigate, ENTER to select
    
    // Массив пунктов меню
    const char *choices[] = {
        "Calculate sum of two numbers",
        "Calculate product of two numbers",
        "Exit",
        NULL
    };
    
    // Инициализация NCurses
    initscr();           // Запуск curses режима
    cbreak();            // Отключение буферизации ввода
    noecho();            // Отключение вывода нажатых клавиш
    keypad(stdscr, TRUE);// Включение обработки спец. клавиш
    
    // Создание пунктов меню
    int n_choices = 0;
    while(choices[n_choices] != NULL) n_choices++;
    
    ITEM **my_items = new ITEM*[n_choices + 1];
    for(int i = 0; i < n_choices; i++) {
        my_items[i] = new_item(choices[i], choices[i]);
    }
    my_items[n_choices] = (ITEM *)NULL;
    
    // Создание меню
    MENU *my_menu = new_menu(my_items);
    
    // Создание окна для меню
    WINDOW *my_menu_win = newwin(10, 40, 4, 4);
    keypad(my_menu_win, TRUE);
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
    set_menu_mark(my_menu, " -> ");
    
    // Отрисовка меню
    box(my_menu_win, 0, 0);
    mvwprintw(my_menu_win, 1, 15, "MY MENU");
    mvprintw(LINES - 2, 0, "Use UP/DOWN arrows, ENTER to select");
    refresh();
    
    post_menu(my_menu);
    wrefresh(my_menu_win);
    
    // Обработка ввода пользователя
    int c;
    ITEM *cur_item;
    bool running = true;
    
    while(running && (c = wgetch(my_menu_win)) != KEY_F(1)) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: // Клавиша ENTER
                cur_item = current_item(my_menu);
                int choice = item_index(cur_item);
                
                if(choice == 0) {
                    // Calculate sum
                    int a, b;
                    echo();
                    curs_set(1);
                    mvwprintw(my_menu_win, 8, 2, "Enter first number: ");
                    wrefresh(my_menu_win);
                    scanw("%d", &a);
                    mvwprintw(my_menu_win, 9, 2, "Enter second number: ");
                    wrefresh(my_menu_win);
                    scanw("%d", &b);
                    noecho();
                    curs_set(0);
                    mvwprintw(my_menu_win, 10, 2, "Sum: %d      ", a + b);
                    wrefresh(my_menu_win);
                    wgetch(my_menu_win);
                    // Очистка сообщений
                    for(int i = 8; i <= 10; i++) {
                        mvwprintw(my_menu_win, i, 2, "                      ");
                    }
                    wrefresh(my_menu_win);
                }
                else if(choice == 1) {
                    // Calculate product
                    int a, b;
                    echo();
                    curs_set(1);
                    mvwprintw(my_menu_win, 8, 2, "Enter first number: ");
                    wrefresh(my_menu_win);
                    scanw("%d", &a);
                    mvwprintw(my_menu_win, 9, 2, "Enter second number: ");
                    wrefresh(my_menu_win);
                    scanw("%d", &b);
                    noecho();
                    curs_set(0);
                    mvwprintw(my_menu_win, 10, 2, "Product: %d      ", a * b);
                    wrefresh(my_menu_win);
                    wgetch(my_menu_win);
                    for(int i = 8; i <= 10; i++) {
                        mvwprintw(my_menu_win, i, 2, "                      ");
                    }
                    wrefresh(my_menu_win);
                }
                else if(choice == 2) {
                    running = false;
                }
                break;
        }
        wrefresh(my_menu_win);
    }
    
    // Очистка памяти и выход
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(int i = 0; i < n_choices; i++) {
        free_item(my_items[i]);
    }
    delete[] my_items;
    endwin();
    
    return 0;
}