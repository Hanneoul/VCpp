#include <stdio.h>
#include <conio.h>

int main()
{
    printf("        마음의 상처\n");
    printf("- 너넨 언제나 제자리걸음 -\n\n\n");

    int count = 0;
    char prev = 'a';
    char current = 'a';
    int err = 0;
    while (current != 27)
    {
        if (count == 0)
            printf("command>");
        prev = current;
        current = _getch();
        count++;

        if (current == 13)  //엔터라면
        {
            printf("\n");


            if (count == 2)
            {
                switch (prev)
                {
                case 'q':
                    printf("종료하는 키는 그게 아니다.\n");
                    break;
                case 'w':
                    printf("저장할수 없는 프로그램이야.\n");
                    break;
                case 'e':
                    printf("e....c...8......\n");
                    break;
                case 'r':
                    printf("rm -rf / \n");
                    break;
                default:
                    err = 1;
                    break;
                }
            }
            else
                err = 1;

            count = 0;

        }
        else
        {
            printf("%c", current);
        }

        if (err == 1)
        {
            printf("ㅂㅅ인가? 다시 입력해주세요.\n");
            err = 0;
        }





    }
    return 0;
}
