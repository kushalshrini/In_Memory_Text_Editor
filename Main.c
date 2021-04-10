#include "text.h"

int main()
{
	WINDOW *win;
	int highlight = 1;
	int choice = 0;
	int c;
	char ch[] = " ";

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	//startx = (80 - WIDTH) / 2;
	//starty = (24 - HEIGHT) / 2;
	
	mvprintw(HEIGHT+1,0,"Press F1 to exit");
	refresh();
	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
	keypad(win, TRUE);
	wmove(win, 0, 0);
	//box(win,0,0);
	wrefresh(win);
	Line *l = init_line();
	int pos =0, x = 0, y = 0;
	mvwprintw(win, HEIGHT-1,0, "pos = %d; y = %d; x = %d; no_of_chars = %d",pos, y, x, l->no_of_chars);
	while(1)
	{	
		c = wgetch(win);
		ch[0] = (char) c;
		switch(c)
		{	
			case KEY_LEFT:
			{
				if(l->no_of_chars+1 > pos)
				{
					if(x > 0)
						wmove(win,y,--x);
					else if(y!=0)
					{
						x = WIDTH-1;
						wmove(win,--y, x);
					}
					pos = calc_pos(y,x);
				}
				break;
			}
			case KEY_RIGHT:
			{
				if(l->no_of_chars+1 > pos+1)
				{
					if(x != WIDTH-1)
						wmove(win,y,++x);
					else if(y!=HEIGHT-1)
					{
						x = 0;
						wmove(win,++y,x);
					}
					pos = calc_pos(y,x);
				}
				break;
			}
			case KEY_DOWN:
			{
				if(l->no_of_chars+1 > pos+WIDTH)
				{
					if(y < HEIGHT-1)
						wmove(win, ++y, x);
					pos = calc_pos(y,x);
				}
				break;
			}
			case KEY_UP:
			{
				if(l->no_of_chars+1 > pos)
				{
					if(y > 0)
						wmove(win, --y, x);
					pos = calc_pos(y,x);
				}
				break;
			}
			case KEY_DC:
			case 127:
			case KEY_BACKSPACE:
			{
				werase(win);
				delete_at_pos(l,pos);
				
				if(x > 0)
					wmove(win,y,--x);
				else if(y!=0)
				{
					x = WIDTH-1;
					wmove(win,--y, x);
				}
				pos = calc_pos(y,x);
				display_gui(l,win);
				mvwprintw(win, HEIGHT-2,0, "Delete char at pos = %d;  No of chars in list = %d", pos, l->no_of_chars-1);
				break;
			}
			case '\t':
			{
				char tab[] = "    ";
				werase(win);
				if(l->no_of_chars+1 > pos)
				{
					l = insert_at_pos(l,pos,tab);
					if(x<WIDTH-1)
						x+=4;
					else if(y<HEIGHT-1)
					{
						x=3;
						y++;
					}
				}
				pos = calc_pos(y,x);
				display_gui(l,win);
				wrefresh(win);
				break;
			}
			case '\n':
			{
				werase(win);
				if(l->no_of_chars+1 > pos)
				{
					if(y < HEIGHT-1)
					{
						for(int i = x; i< WIDTH; i++)
						{
							l = insert_at_pos(l,pos," ");
							if(x<WIDTH-1)
								x++;
							else if(y<HEIGHT-1)
							{
								x=0;
								y++;
							}
						}
					}
				}
				pos = calc_pos(y,x);
				display_gui(l,win);
				wrefresh(win);
				break;
			}
			case KEY_F(1):
			{
				clrtoeol();
				refresh();
				endwin();
				exit(0);
				break;
			}
			default:
			{
				werase(win);
				if(x < WIDTH-1 || y < HEIGHT-1)
				{
					if(l->no_of_chars+1 > pos)
					{
						l = insert_at_pos(l,pos,ch);
						if(x<WIDTH-1)
							x++;
						else if(y<HEIGHT-1)
						{
							x=0;
							y++;
						}
					}
				}
				pos = calc_pos(y,x);
				display_gui(l,win);
				mvwprintw(win, HEIGHT-2,0, "Insert '%c' at pos = %d;  No of chars in list = %d", ch[0], pos, l->no_of_chars+1);
				//wrefresh(win);
				break;
			}
				//refresh();
		}
		mvwprintw(win, HEIGHT-1,0, "pos = %d; y = %d; x = %d; No of chars in list = %d",pos, y, x, l->no_of_chars);
		//mvwprintw(win,HEIGHT-1,0,"Press F1 to exit");
		wmove(win, y, x);
		wrefresh(win);
	}	
	//mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();
	refresh();
	endwin();
	return 0;
}