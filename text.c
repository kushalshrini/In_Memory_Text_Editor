#include "text.h"


Line* convert_str_to_chs(char *str)
{
	Line *l = (Line*)malloc(sizeof(Line*));
	l->no_of_chars = strlen(str);
	Ch *temp, *prev;
	for(int i = 0; i < l->no_of_chars; i++)
	{
		temp = (Ch*)malloc(sizeof(Ch*));
		temp->ch = str[i];
		if(i == 0)
		{
			l->first_char = temp;
			prev = temp;
		}
		else
		{
			temp->prev = prev;
			prev->next = temp;
			prev = temp;
		}
	}
	l->last_char = prev;
	return l;
}

Ch* findPos(Line *l, int pos)
{
	Ch *temp = l->first_char;
	int i = 1;
	if(pos == 0)
		return NULL;
	while(i<pos)
	{
		temp=temp->next;
		i++;
	}
	return temp;
}

Line* insert_line(Line *l, Ch *pos, Line *temp)
{
	int chars = 0;
	
	chars = temp->no_of_chars;
	l->no_of_chars += chars;

	// if Line is empty
	if(l->first_char == NULL)
	{
		l = temp;
		return l;
	}
	Ch *pos2;
	
	if(pos != NULL)
		pos2 = pos->next;
	else
		pos2 = l->first_char;	
	
	if(pos != NULL)
		pos->next = temp->first_char;
	else
		l->first_char = temp->first_char;

	(temp->first_char)->prev = pos;

	if(pos2 != NULL)
		pos2->prev = temp->last_char;
	else
		l->last_char = temp->last_char;
	(temp->last_char)->next = pos2;

	return l;
}

Line* insert_at_pos(Line *l, int position, char *str)
{
	if(position > l->no_of_chars+1)
		return l;
	Line *temp;
	//mvprintw(HEIGHT+2, 0, "before %s", str);
	temp = convert_str_to_chs(str);
	//mvprintw(HEIGHT+3, 0, "temp-> strlen %c", (temp->first_char)->ch);
	//refresh();
	Ch *pos = findPos(l, position);	
	l = insert_line(l, pos, temp);

	return l;
}

Line* delete_at_pos(Line *l, int position)
{
	if(position > l->no_of_chars+1)
		return l;
	Ch *c = findPos(l, position);
	if(c != NULL)
		delete_char(l,c);
	return l;
}

Line* delete_char(Line *l, Ch* c)
{
	Ch *next = c->next;
	Ch *prev = c->prev;
	if(next != NULL)
		next->prev = prev;
	else
		l->last_char = prev;
	if(prev != NULL)
		prev->next = next;
	else
		l->first_char = next;
	l->no_of_chars -= 1;
	free(c);
	return l;
}

void display(Line *l)
{
	Ch *cur = l->first_char;
	while(cur != NULL)
	{
		//printf("%c", cur->ch); // use for non GUI interface
		printw("%c", cur->ch);
		cur = cur->next;
	}
	//printf("\n"); // use for non GUI interface
}

void display_gui(Line *l, WINDOW *win)
{
	werase(win);
	Ch *cur = l->first_char;
	wmove(win,0,0);
	while(cur != NULL)
	{
		if(cur->ch != '\0')
			wprintw(win, "%c", cur->ch);
		cur = cur->next;
	}
	//wrefresh(win);
}

Line* init_line()
{
	Line *l = (Line*)malloc(sizeof(Line*));
	l->no_of_chars = 0;
	l->first_char = NULL;
	l->last_char = NULL;
}

int calc_pos(int y, int x)
{
	return (WIDTH*y)+x;
}
/*
void convert_str_to_words(char *str, Word *wFront, Word *wEnd, int *chars, int *words)
{
	int wds = 0;
	int chs = strlen(str);
	*chars = chs;
	Word *temp, *prev;
	char *ptr = strtok(str, " ");
	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		temp = (Word*)malloc(sizeof(Word*));
		temp->size = strlen(ptr);
		temp->chs = (char*) malloc(temp->size*sizeof(char*));
		strcpy(temp->chs, ptr);
		printf("'%s'\n", temp->chs);
		temp->next = NULL;
		temp->prev = NULL;
		if(wds == 0)
			wFront = temp;
		else
		{
			temp->prev = prev;
			prev->next = temp;
			prev = temp;
		}
		wds += 1;
	}
	wEnd = prev;
}
*/

/*
int insert(Lines *lines, char *str)
{
	Line *line = (Line*)malloc(sizeof(Line*));
	line->no_of_chars = strlen(str);
	line->words = 0;
	Word *temp, *prev;
	int init_size = strlen(str);
	char *ptr = strtok(str, " ");
	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		temp = (Word*)malloc(sizeof(Word*));
		temp->size = strlen(ptr);
		temp->chs = (char*) malloc(temp->size*sizeof(char*));
		strcpy(temp->chs, ptr);
		printf("'%s'\n", temp->chs);
		temp->next = NULL;
		temp->prev = NULL;
		if(line->first_word == NULL){
			line->first_word = temp;
			prev = temp;
		}else{
			prev->next = temp;
			temp->prev = prev;
			prev = temp;
		}
		line->words += 1;
		ptr = strtok(NULL, delim);
	}
	if(lines->first_line == NULL)
}
void addLine(Lines *l, Line *ll)
{
	if(l->first_line == NULL)
		l->first_line = ll;
	else{
		(l->last_line)->next = ll;
		ll->prev = (l->last_line)
	}
}
int insert_at_pos(Lines *lines, Line *line, Word *word, char *st)
{
}
 */


/*
int main()
{
	//char str[] = "strtok needs to be called several times to split a string";
	char str[] = "strtok";
	Line l = (Line)malloc(sizeof(Line));
	l->no_of_chars = 0;
	l = insert_at_pos(l,1,str);
	int choice = 1, pos = 0;
	while(choice != 4)
	{
		char s[1000];
		//display(l);
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				printf("Enter the text\n");
				scanf("%s",s);
				printf("Enter the position for insertion\n");
				scanf("%d", &pos);
				l = insert_at_pos(l,pos,s);
				display(l);
				//printf("%d\n",l->no_of_chars);
				break;
			case 2:
				printf("Enter pos to delete\n");
				scanf("%d", &pos);
				l = delete_at_pos(l, pos);
				display(l);
				//printf("%d\n",l->no_of_chars);
				break;
			case 3: 
				display(l);
				//printf("%d\n",l->no_of_chars);
			case 4:
				break;
			default:
				printf("Wrong Input selected\n");
		}
	}
	
	return 0;
}
*/