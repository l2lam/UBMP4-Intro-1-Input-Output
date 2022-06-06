// LCD Functions Developed by electroSome
#define RS H1OUT
#define EN H2OUT
#define LD4 H3OUT
#define LD5 H4OUT
#define LD6 H5OUT
#define LD7 H6OUT

void Lcd_Port(char a)
{
    if (a & 1)
        LD4 = 1;
    else
        LD4 = 0;

    if (a & 2)
        LD5 = 1;
    else
        LD5 = 0;

    if (a & 4)
        LD6 = 1;
    else
        LD6 = 0;

    if (a & 8)
        LD7 = 1;
    else
        LD7 = 0;
}
void Lcd_Cmd(char a)
{
    RS = 0; // => RS = 0
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear()
{
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
    char temp, z, y;
    if (a == 1)
    {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
    else if (a == 2)
    {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}

void Lcd_Init()
{
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);
    /////////////////////////////////////////////////////
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a)
{
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1;           // => RS = 1
    Lcd_Port(y >> 4); // Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
    Lcd_Port(temp);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a)
{
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right()
{
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left()
{
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}
