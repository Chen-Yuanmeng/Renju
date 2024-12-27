#include "check.h"

// Check entrance function: start check of all things
// return `int`:
//     0000 - passed check;
//     others - failed check
int check(int board_state[][BOARD_SIZE], int last_put[], int next) {
    return (
        check_win(board_state, last_put, next) +
        check_forbidden_move(board_state, last_put, next) +
        check_full_board(board_state, last_put)
    );
}

// Check win function: check if anyone wins
// return `int`:
//     00 - Nobody wins;
//     01 - Black wins;
//     02 - White wins;
int check_win(int board_state[][BOARD_SIZE], int last_put[], int next) {
    int order;
    int x_row = last_put[0];
    int y_column = last_put[1];

    if (next == BLACK) {
        order = WHITE;
    }
    else {
        order = BLACK;
    }

        int i, j, x, y, flag;

    //'-'横着方向赢
    x = x_row;            //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;      //x是行; y是列;
    flag = 0;
    for (i = 0; i < 9; y++, i++) {
        if (y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        if (board_state[x][y] == order) {
            flag++;
        }
        else if (flag >= 5) {
            break;
        }
        else {
            flag = 0;
        }
    }
    if ((WHITE == order && flag >= 5) || (BLACK == order && flag == 5)) {
        return order;
    }

    //'|'竖着方向赢
    x = x_row - 4;     //获取刚下棋坐标的开始循环坐标
    y = y_column;      //x是行; y是列;
    flag = 0;
    for (i = 0; i < 9; x++, i++) {
        if (x < 0 || x >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        if (board_state[x][y] == order) {
            flag++;
        }
        else if (flag >= 5) {
            break;
        }
        else {
            flag = 0;
        }
    }
    if ((WHITE == order && flag >= 5) || (BLACK == order && flag == 5)) {
        return order;
    }

    //'/'斜杠方向赢
    x = x_row - 4;     //获取刚下棋坐标的开始循环坐标
    y = y_column + 4;  //x是行; y是列;
    flag = 0;
    for (i = 0; i < 9; x++, y--, i++) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        if (board_state[x][y] == order) {
            flag++;
        }
        else if (flag >= 5) {
            break;
        }
        else {
            flag = 0;
        }
    }
    if ((WHITE == order && flag >= 5) || (BLACK == order && flag == 5))
        return order;

    //'\'斜杠方向赢
    x = x_row - 4;     //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;  //x是行; y是列;
    flag = 0;
    for (i = 0; i < 9; x++, y++, i++) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        if (board_state[x][y] == order) {
            flag++;
        }
        else if (flag >= 5) {
            break;
        }
        else {
            flag = 0;
        }
    }
    if ((WHITE == order && flag >= 5) || (BLACK == order && flag == 5)) {
        return order;
    }

    return NONE;
}

// Check forbidden function: check if Black has performed forbidden moves
// return `int`:
//     000 - No forbidden moves;
//     010 - Black has forbidden moves;
int check_forbidden_move(int board_state[][BOARD_SIZE], int last_put[], int next) {
    if (next == WHITE) {
        return 8 * (!!(is_forbidden_move(board_state, last_put[0], last_put[1])));
    }
    return 0;
}

// Check full function: check if board is full
// return `int`:
//     0000 - not full;
//     0100 - full
int check_full_board(int board_state[][BOARD_SIZE], int last_put[]) {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (!board_state[r][c]) {
                return 0;
            }
        }
    }
    return 0100;
}


/**
 * @brief 禁手规则检查
 * @param[in] board_state    棋盘二级指针
 * @param[in] x_row    要检查点的行坐标
 * @param[in] y_column 要检查点的列坐标
 * @retval 0 无禁手
 * @retval 1 三三禁手
 * @retval 2 四四禁手
 * @retval 3 长连禁手
 */
int is_forbidden_move(int board_state[][BOARD_SIZE], int x_row, int y_column) {
    if (check_overline(board_state, x_row, y_column)) {
        return 3;
    }
    if (check_double_four(board_state, x_row, y_column)) {
        return 2;
    }
    if (check_double_three(board_state, x_row, y_column)) {
        return 1;
    }
    return 0;
}

/**
 * @brief 三三禁手检查
 * @param[in] board_state    棋盘二级指针
 * @param[in] x_row    要检查点的行坐标
 * @param[in] y_column 要检查点的列坐标
 * @retval 0 无禁手
 * @retval 1 有三三禁手
 */
int check_double_three(int board_state[][BOARD_SIZE], int x_row, int y_column) {
    // Situation around the chess piece, '0': blank; '1': BLACK; '2': WHITE; '4': no_board;
    char chess[10];

    int i;
    int x;              // Line number
    int y;              // Column number
    int addr;           // Address offset of found string
    int count = 0;      // Number of three's
    int is_fake;        // Flag whether it is fake

    // On lines (-)
    x = x_row;
    y = y_column - 4;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");     // Initialize chess str

    for (i = 0; i < 9; y++, i++) {
        if (y < 0 || y >= BOARD_SIZE)   // Don't do anything if out of chess board
            continue;
        chess[i] = board_state[x][y] + '0';
    }

    addr = strstr(chess, "01110") - chess; //配对字符串在原字符串的下标
    is_fake = 0;                          //假活三标志位
    if (addr >= 0 && addr <= 9) {
        //检查"01110"的"0"是否禁手 && "01110"的前后是否有个为空,且不是禁手
        board_state[x_row][y_column - 4 + addr] = BLACK;   //"01110"的第一个"0"放黑棋
        if (is_forbidden_move(board_state, x_row, y_column - 4 + addr)) {
            is_fake = 1;
        }
        board_state[x_row][y_column - 4 + addr] = NONE;   //恢复"01110"的第一个"0"
        board_state[x_row][y_column + addr] = BLACK;      //"01110"的第二个"0"放黑棋
        if (is_forbidden_move(board_state, x_row, y_column + addr)) {
            is_fake = 1;
        }
        board_state[x_row][y_column + addr] = NONE;       //恢复"01110"的第二个"0"
        if (!is_fake && y_column - 5 + addr >= 0 && !board_state[x_row][y_column - 5 + addr]) { //"01110"的前为空
            board_state[x_row][y_column - 5 + addr] = BLACK;
            if (0 == is_forbidden_move(board_state, x_row, y_column - 5 + addr)) { //检查此点是否为禁手
                count++;
            }
            board_state[x_row][y_column - 5 + addr] = NONE;
        }
        else if (0 == is_fake && y_column + 1 + addr < BOARD_SIZE && 0 == board_state[x_row][y_column + 1 + addr]) {//"01110"的后为空
            board_state[x_row][y_column + 1 + addr] = BLACK;
            if (0 == is_forbidden_move(board_state, x_row, y_column + 1 + addr)) { //检查此点是否为禁手
                count++;
            }
            board_state[x_row][y_column + 1 + addr] = NONE;
        }
    }
    //检查"跳三"的情况1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        board_state[x_row][y_column - 2 + addr] = BLACK;           //"010110"中间的"0"放黑棋
        if (0 == is_forbidden_move(board_state, x_row, y_column - 2 + addr)) { //检查此点是否为禁手
            count++;
        }
        board_state[x_row][y_column - 2 + addr] = NONE;            //恢复"010110"中间的"0"
    }
    //检查"跳三"的情况2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        board_state[x_row][y_column - 1 + addr] = BLACK;           //"011010"中间的"0"放黑棋
        if (0 == is_forbidden_move(board_state, x_row, y_column - 1 + addr)) { //检查此点是否为禁手
            count++;
        }
        board_state[x_row][y_column - 1 + addr] = NONE;            //恢复"011010"中间的"0"
    }

    //'|'竖着方向禁手规则
    x = x_row - 4;        //获取刚下棋坐标的开始循环坐标
    y = y_column;         //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, i++) {
        if (x < 0 || x >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        chess[i] = board_state[x][y] + 48;
    }
    //检查"活三"的情况
    addr = strstr(chess, "01110") - chess; //配对字符串在原字符串的下标
    is_fake = 0;                          //假活三标志位
    if (addr >= 0 && addr <= 9) {
        //检查"01110"的"0"是否禁手 && "01110"的前后是否有个为空,且不是禁手
        board_state[x_row - 4 + addr][y_column] = BLACK;   //"01110"的第一个"0"放黑棋
        if (0 != is_forbidden_move(board_state, x_row - 4 + addr, y_column)) {
            is_fake = 1;
        }
        board_state[x_row - 4 + addr][y_column] = NONE;   //恢复"01110"的第一个"0"
        board_state[x_row + addr][y_column] = BLACK;      //"01110"的第二个"0"放黑棋
        if (0 != is_forbidden_move(board_state, x_row + addr, y_column)) {
            is_fake = 1;
        }
        board_state[x_row + addr][y_column] = NONE;       //恢复"01110"的第二个"0"
        if (0 == is_fake && x_row - 5 + addr >= 0 && 0 == board_state[x_row - 5 + addr][y_column]) { //"01110"的前为空
            board_state[x_row - 5 + addr][y_column] = BLACK;
            if (0 == is_forbidden_move(board_state, x_row - 5 + addr, y_column)) { //检查此点是否为禁手
                count++;
            }
            board_state[x_row - 5 + addr][y_column] = NONE;
        }
        else if (0 == is_fake && x_row + 1 + addr < BOARD_SIZE && 0 == board_state[x_row + 1 + addr][y_column]) {//"01110"的后为空
            board_state[x_row + 1 + addr][y_column] = BLACK;
            if (0 == is_forbidden_move(board_state, x_row + 1 + addr, y_column)) { //检查此点是否为禁手
                count++;
            }
            board_state[x_row + 1 + addr][y_column] = NONE;
        }
    }
    //检查"跳三"的情况1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        board_state[x_row - 2 + addr][y_column] = BLACK;           //"010110"中间的"0"放黑棋
        if (0 == is_forbidden_move(board_state, x_row - 2 + addr, y_column)) { //检查此点是否为禁手
            count++;
        }
        board_state[x_row - 2 + addr][y_column] = NONE;            //恢复"010110"中间的"0"
    }
    //检查"跳三"的情况2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        board_state[x_row - 1 + addr][y_column] = BLACK;           //"011010"中间的"0"放黑棋
        if (0 == is_forbidden_move(board_state, x_row - 1 + addr, y_column)) { //检查此点是否为禁手
            count++;
        }
        board_state[x_row - 1 + addr][y_column] = NONE;            //恢复"011010"中间的"0"
    }

    //'/'斜杠方向禁手规则
    x = x_row - 4;          //获取刚下棋坐标的开始循环坐标
    y = y_column + 4;       //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, y--, i++) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        chess[i] = board_state[x][y] + 48;
    }
    //检查"活三"的情况
    addr = strstr(chess, "01110") - chess; //配对字符串在原字符串的下标
    is_fake = 0;                          //假活三标志位
    if (addr >= 0 && addr <= 9) {
        //检查"01110"的"0"是否禁手 && "01110"的前后是否有个为空,且不是禁手
        board_state[x_row - 4 + addr][y_column + 4 - addr] = BLACK;   //"01110"的第一个"0"放黑棋
        if (0 != is_forbidden_move(board_state, x_row - 4 + addr, y_column + 4 - addr)) {
            is_fake = 1;
        }
        board_state[x_row - 4 + addr][y_column + 4 - addr] = NONE;   //恢复"01110"的第一个"0"
        board_state[x_row + addr][y_column - addr] = BLACK;      //"01110"的第二个"0"放黑棋
        if (0 != is_forbidden_move(board_state, x_row + addr, y_column - addr)) {
            is_fake = 1;
        }
        board_state[x_row + addr][y_column - addr] = NONE;       //恢复"01110"的第二个"0"
        if (0 == is_fake && x_row - 5 + addr >= 0 && y_column + 5 - addr < BOARD_SIZE && 0 == board_state[x_row - 5 + addr][y_column + 5 - addr]) { //"01110"的前为空
            board_state[x_row - 5 + addr][y_column + 5 - addr] = BLACK;
            if (0 == is_forbidden_move(board_state, x_row - 5 + addr, y_column + 5 - addr)) { //检查此点是否为禁手
                count++;
            }
            board_state[x_row - 5 + addr][y_column + 5 - addr] = NONE;
        }
        else if (0 == is_fake && x_row + 1 + addr < BOARD_SIZE && y_column - 1 - addr >= 0 && 0 == board_state[x_row + 1 + addr][y_column - 1 - addr]) {//"01110"的后为空
            board_state[x_row + 1 + addr][y_column - 1 - addr] = BLACK;
            if (0 == is_forbidden_move(board_state, x_row + 1 + addr, y_column - 1 - addr)) { //检查此点是否为禁手
                count++;
            }
            board_state[x_row + 1 + addr][y_column - 1 - addr] = NONE;
        }
    }
    //检查"跳三"的情况1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        board_state[x_row - 2 + addr][y_column + 2 - addr] = BLACK;           //"010110"中间的"0"放黑棋
        if (0 == is_forbidden_move(board_state, x_row - 2 + addr, y_column + 2 - addr)) { //检查此点是否为禁手
            count++;
        }
        board_state[x_row - 2 + addr][y_column + 2 - addr] = NONE;            //恢复"010110"中间的"0"
    }
    //检查"跳三"的情况2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        board_state[x_row - 1 + addr][y_column + 1 - addr] = BLACK;           //"011010"中间的"0"放黑棋
        if (0 == is_forbidden_move(board_state, x_row - 1 + addr, y_column + 1 - addr)) { //检查此点是否为禁手
            count++;
        }
        board_state[x_row - 1 + addr][y_column + 1 - addr] = NONE;            //恢复"011010"中间的"0"
    }

    //'\'反斜杠方向禁手规则
    x = x_row - 4;          //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;       //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, y++, i++) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        chess[i] = board_state[x][y] + 48;
    }
    //检查"活三"的情况
    addr = strstr(chess, "01110") - chess; //配对字符串在原字符串的下标
    is_fake = 0;                          //假活三标志位
    if (addr >= 0 && addr <= 9) {
        //检查"01110"的"0"是否禁手 && "01110"的前后是否有个为空,且不是禁手
        board_state[x_row - 4 + addr][y_column - 4 + addr] = BLACK;   //"01110"的第一个"0"放黑棋
        if (0 != is_forbidden_move(board_state, x_row - 4 + addr, y_column - 4 + addr)) {
            is_fake = 1;
        }
        board_state[x_row - 4 + addr][y_column - 4 + addr] = NONE;   //恢复"01110"的第一个"0"
        board_state[x_row + addr][y_column + addr] = BLACK;      //"01110"的第二个"0"放黑棋
        if (0 != is_forbidden_move(board_state, x_row + addr, y_column + addr)) {
            is_fake = 1;
        }
        board_state[x_row + addr][y_column + addr] = NONE;       //恢复"01110"的第二个"0"
        if (0 == is_fake && x_row - 5 + addr >= 0 && y_column - 5 + addr >= 0 && 0 == board_state[x_row - 5 + addr][y_column - 5 + addr]) { //"01110"的前为空
            board_state[x_row - 5 + addr][y_column - 5 + addr] = BLACK;
            if (0 == is_forbidden_move(board_state, x_row - 5 + addr, y_column - 5 + addr)) { //检查此点是否为禁手
                count++;
            }
            board_state[x_row - 5 + addr][y_column - 5 + addr] = NONE;
        }
        else if (0 == is_fake && x_row + 1 + addr < BOARD_SIZE && y_column + 1 + addr < BOARD_SIZE && 0 == board_state[x_row + 1 + addr][y_column + 1 + addr]) {//"01110"的后为空
            board_state[x_row + 1 + addr][y_column + 1 + addr] = BLACK;
            if (0 == is_forbidden_move(board_state, x_row + 1 + addr, y_column + 1 + addr)) { //检查此点是否为禁手
                count++;
            }
            board_state[x_row + 1 + addr][y_column + 1 + addr] = NONE;
        }
    }
    //检查"跳三"的情况1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        board_state[x_row - 2 + addr][y_column - 2 + addr] = BLACK;           //"010110"中间的"0"放黑棋
        if (0 == is_forbidden_move(board_state, x_row - 2 + addr, y_column - 2 + addr)) { //检查此点是否为禁手
            count++;
        }
        board_state[x_row - 2 + addr][y_column - 2 + addr] = NONE;            //恢复"010110"中间的"0"
    }
    //检查"跳三"的情况2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        board_state[x_row - 1 + addr][y_column - 1 + addr] = BLACK;           //"011010"中间的"0"放黑棋
        if (0 == is_forbidden_move(board_state, x_row - 1 + addr, y_column + 1 - addr)) { //检查此点是否为禁手
            count++;
        }
        board_state[x_row - 1 + addr][y_column - 1 + addr] = NONE;            //恢复"011010"中间的"0"
    }

    return count > 1 ? 1 : 0;  //若超过1个活三/跳三, 返回1; 否则返回0

}

/**
 * @brief 四四禁手检查
 * @param[in] board_state    棋盘二级指针
 * @param[in] x_row    要检查点的行坐标
 * @param[in] y_column 要检查点的列坐标
 * @retval 0 无禁手
 * @retval 1 有四四禁手
 */
int check_double_four(int board_state[][BOARD_SIZE], int x_row, int y_column) {
    char chess[10]; //棋子周围情况, 0:空棋盘; 1:黑棋; 2:白棋; 4:无棋盘;
    int i, x, y, count = 0; //count为活三/跳三的数, 范围: 0~4

    //'-'横着方向禁手规则
    x = x_row;          //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;   //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; y++, i++) {
        if (y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        chess[i] = board_state[x][y] + 48;
    }
    if (NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
        NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
        NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'|'竖着方向禁手规则
    x = x_row - 4;        //获取刚下棋坐标的开始循环坐标
    y = y_column;         //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, i++) {
        if (x < 0 || x >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        chess[i] = board_state[x][y] + 48;
    }
    if (NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
        NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
        NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'/'斜杠方向禁手规则
    x = x_row - 4;          //获取刚下棋坐标的开始循环坐标
    y = y_column + 4;       //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, y--, i++) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        chess[i] = board_state[x][y] + 48;
    }
    if (NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
        NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
        NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'\'反斜杠方向禁手规则
    x = x_row - 4;          //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;       //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, y++, i++) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        chess[i] = board_state[x][y] + 48;
    }
    if (NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
        NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
        NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    return count > 1 ? 1 : 0;  //若超过1个活四/冲四/跳四, 返回1; 否则返回0
}

/**
 * @brief 长连禁手检查
 * @param[in] board_state    棋盘二级指针
 * @param[in] x_row    要检查点的行坐标
 * @param[in] y_column 要检查点的列坐标
 * @retval 0 无禁手
 * @retval 1 有长连禁手
 */
int check_overline(int board_state[][BOARD_SIZE], int x_row, int y_column) {
    int x, y, i, flag;

    //'-'横着方向禁手规则
    x = x_row;          //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;   //x是行; y是列;
    flag = 0;
    for (i = 0; i < 9; y++, i++) {
        if (y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        if (board_state[x][y] == BLACK) {
            flag++;
        }
        else {
            flag = 0;
        }
        if (6 == flag) {
            return 1;
        }
    }

    //'|'竖着方向禁手规则
    x = x_row - 4;     //获取刚下棋坐标的开始循环坐标
    y = y_column;      //x是行; y是列;
    flag = 0;
    for (i = 0; i < 9; x++, i++) {
        if (x < 0 || x >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        if (board_state[x][y] == BLACK) {
            flag++;
        }
        else {
            flag = 0;
        }
        if (6 == flag) {
            return 1;
        }
    }

    //'/'斜杠方向禁手规则
    x = x_row - 4;       //获取刚下棋坐标的开始循环坐标
    y = y_column + 4;    //x是行; y是列;
    flag = 0;
    for (i = 0; i < 9; x++, y--, i++) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        if (board_state[x][y] == BLACK) {
            flag++;
        }
        else {
            flag = 0;
        }
        if (6 == flag) {
            return 1;
        }
    }

    //'\'反斜杠方向禁手规则
    x = x_row - 4;       //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;    //x是行; y是列;
    flag = 0;
    for (i = 0; i < 9; x++, y++, i++) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) //超出棋盘则跳出
            continue;
        if (board_state[x][y] == BLACK) {
            flag++;
        }
        else {
            flag = 0;
        }
        if (6 == flag) {
            return 1;
        }
    }
    return 0;
}

