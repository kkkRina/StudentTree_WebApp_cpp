#include <iostream>
#include <fstream>
#include "tree.h"
#include "structs.h"
#include "queue.h"
using namespace  std;
enum traverse_type { prefix, infix, postfix, wide };

void show_elems(tree t, traverse_type tt)
{
	queue q;
	switch (tt)
	{
	case prefix: q = prefix_traverse(t); break;
	case infix: q = infix_traverse(t); break;
	case postfix: q = postfix_traverse(t); break;
	case wide: q = wide_traverse(t); break;
	}
	auto curr = q.first;
	while (curr)
	{
		const auto v = curr->tree_node;
		if (!v) cout << "[-]";
		else cout << (v->v.x) << "(" << v->v.surname << ")";
		cout << " ";
		curr = curr->next;
	}
	cout << endl;
	clear(q);
}
void show_any_elems(tree t, traverse_type tt, char* letter)
{
	queue q;
	switch (tt)
	{
	case prefix: q = prefix_traverse(t); break;
	case infix: q = infix_traverse(t); break;
	case postfix: q = postfix_traverse(t); break;
	case wide: q = wide_traverse(t); break;
	}
	auto curr = q.first;
	while (curr)
	{
		const auto v = curr->tree_node;
		if (!v) cout << "[-]";
		else if (v->v.surname[0]==letter[0])
		{
			cout << (v->v.x) << (v->v.surname);////
		}
		cout << " ";
		curr = curr->next;
	}
	cout << endl;
	clear(q);
}
char* decode(char* word);
char* substr(char* arr, int begin, int len);
int append(char* s, size_t size, char c);
char* get_menu(const char* menu_filename);
char* get_content();
char* parse(const char* buf);
void load_content(const char* template_name);
void show_fam_elems(tree t, traverse_type tt, char* letter);
void show_ball_elems(tree t, traverse_type tt, int ball);

void main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Content-type: text/html; charset=windows-1251\n\n";
	load_content("tree.html");
}
char* decode(char* word)
{
	const int sz = 4096;
	char* new_str = new char[sz];
	new_str[0] = 0;
	char a;
	int j;

	for (int i = 0; i < strlen(word); i++)
	{
		if (word[i] == '+')
		{
			append(new_str, sz, ' ');
		}
		else if (word[i] == '%')
		{
			sscanf_s(substr(word, i + 1, 2), "%x", &j);
			a = static_cast<char>(j);
			append(new_str, sz, a);
			i = i + 2;
		}
		else
		{
			append(new_str, sz, word[i]);
		}
	}
	return (new_str);
}
char* substr(char* arr, int begin, int len)
{
	char* res = new char[len + 1];
	for (int i = 0; i < len; i++)
		res[i] = *(arr + begin + i);
	res[len] = 0;
	return res;
}
int append(char* s, size_t size, char c)
{
	if (strlen(s) + 1 >= size)
	{
		return 1;
	}
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
return 0;
}
char* get_menu(const char* menu_filename)
{
	ifstream mf(menu_filename);
	const size_t res_sz = 65535;
	char* res = new char[res_sz];
	res[0] = 0;
	if (mf.is_open())
	{
		char* menuline = new char[1024];
		while (!mf.eof())
		{
			mf.getline(menuline, 1024);
			char* title;
			char* page = strtok_s(menuline, " ", &title);
			strcat_s(res, res_sz, "<div class='menuitem'>");
			strcat_s(res, res_sz, "<a href='");
			strcat_s(res, res_sz, page);
			strcat_s(res, res_sz, "'>");
			strcat_s(res, res_sz, title);
			strcat_s(res, res_sz, "</a></div>\n");
		}
		delete[] menuline;
		mf.close();
	}
	return res;
}
char* get_content()
{
	char* text = new char[40960];
	
	char* token;
	size_t len;
	errno_t err = _dupenv_s(&text, &len, "QUERY_STRING");
	if (strcmp(text, "") != 0)
	{
		char* texx = decode(text);
		char* p = strtok_s(texx, "&", &token); 

		char* w = strtok_s(NULL, "&", &token); 

		char* f = strtok_s(NULL, "&", &token); 
		
		char* l = strtok_s(NULL, "&", &token); 

		char* b = strtok_s(NULL, "&", &token); 

		char* exp = strtok_s(p, "=", &token);

		char* pch = strtok_s(NULL, "\r\n", &token);
		
		ofstream pe;
		pe.open("chel.txt");
		if (pe.is_open())
		{
			while (pch != NULL)
			{
				pe << pch << endl;
				pch = strtok_s(NULL, "\r\n", &token);
			}
		}
		pe.close();
		char* way = strtok_s(w, "=", &token);
		char* fexp = strtok_s(f, "=", &token);
		char* surname = strtok_s(NULL,"\n",&token);//Фамилия
		char* lexp = strtok_s(l, "=", &token);
		char* letter = strtok_s(NULL, "\n", &token); // Буква
		char* bexp = strtok_s(b, "=", &token);
		char* bal = strtok_s(NULL, "\n", &token); 
		int ascore = atoi(bal); //Балл
		tree tr;
		ifstream pep("chel.txt");

		if (pep.is_open())
		{

			while (!pep.eof())
			{

				int sz = 1024;

				char* str = new char[sz];
				char* name = new char[sz];
				char* in = new char[sz];
				char* ball = new char[sz];
				int score;
				char* new_token;
				
				pep.getline(str, sz);// ???????
				cout << str << endl;
				char* pc = strtok_s(str, "*", &new_token);
				while (pc != NULL)
				{
					char s1[50];
					strcpy_s(s1, pc);
					char* s = decode(s1);
					pc = strtok_s(NULL, "*", &new_token);
					name = strtok_s(s, " ", &new_token);
					ball = strtok_s(NULL, " ", &new_token);
					cout << name << " " << ball << endl;
					score = atoi(ball);
					value v;
					v.x = score;
					v.surname = name;
					add(tr, v, letter);
					
				}
			}
		}
		pep.close();

		show_elems(tr, infix);

		if (strcmp(way, "letter") == 0)
		{
			show_any_elems(tr, infix, letter);
		}
		else if (strcmp(way, "surname") == 0)
		{
			show_fam_elems(tr, infix, surname);
		}
		else if (strcmp(way, "ascore") == 0)
		{
			show_ball_elems(tr, infix, ascore);
		}
		drop(tr);
	}

	const size_t res_sz = 65535;
	char* res = new char[res_sz];
	res[0] = 0;
	strcat_s(res, res_sz, "<form method='get' action='tree.cgi'>\n ");
	strcat_s(res, res_sz, "<label for='list'' class = 'form - ooo color - text''>Введите список студентов: <br>\n");
	strcat_s(res, res_sz, "</label>\n");
	strcat_s(res, res_sz, "<textarea type='text' name='exp' id='exp' rows='10' cols='60' required></textarea><br><br>\n");

	strcat_s(res, res_sz, "<div class='form - button''>\n");
	strcat_s(res, res_sz, "<div>\n <input type = \'checkbox\' id = \'surname\' name = \'surname\'>\n <label for = \'surname\'> Поиск по фамилии </label><br><br>\n </div>");
	strcat_s(res, res_sz, "<label for='exp'' class = 'form - ooo color - text''>Введите фамилию: <br>\n");
	strcat_s(res, res_sz, "</label>\n");
	strcat_s(res, res_sz, "<textarea type='text' name='exp' id='exp' rows='1' cols='20' ></textarea><br><br>\n");

	strcat_s(res, res_sz, "<div>\n <input type = \'checkbox\' id = \'letter\' name = \'letter\'>\n <label for = \'letter\'> Поиск по первой букве </label><br><br>\n </div>");
	strcat_s(res, res_sz, "<label for='exp'' class = 'form - ooo color - text''>Введите первую букву фамилии: <br>\n");
	strcat_s(res, res_sz, "</label>\n");
	strcat_s(res, res_sz, "<textarea type='text' name='exp' id='exp' rows='1' cols='20' ></textarea><br><br>\n");
	
	strcat_s(res, res_sz, "<div>\n <input type = \'checkbox\' id = \'ascore\' name = \'ascore\'>\n <label for = \'ascore\'> Поиск по среднему баллу </label></div><br>");
	strcat_s(res, res_sz, "<label for='exp'' class = 'form - ooo color - text''>Введите балл: <br>\n");
	strcat_s(res, res_sz, "</label>\n");
	strcat_s(res, res_sz, "<textarea type='text' name='exp' id='exp' rows='1' cols='20' ></textarea><br><br>\n");

	strcat_s(res, res_sz, "<input type='submit' class='submit - button' value='Вывести'>\n");
	strcat_s(res, res_sz, "</div>\n");
	strcat_s(res, res_sz, "</form>\n");
	return res;
	
}
char* parse(const char* buf)
{
	char* res;
	if (!strcmp(buf, "<!--menu-->"))
	{
		res = get_menu("menu.txt");
	}
	else if (!strcmp(buf, "<!--content-->"))
	{
		res = get_content();
	}
	else
	{
		res = new char[strlen(buf) + 1];
		strcpy_s(res, strlen(buf) + 1, buf);
	}
	return res;
}
void load_content(const char* template_name)
{
	ifstream tf(template_name);
	if (tf.is_open())
	{
		const size_t buf_sz = 65535;
		char* buf = new char[buf_sz];
		while (!tf.eof())
		{
			tf.getline(buf, buf_sz);
			char* parsed_buf = parse(buf);
			cout << parsed_buf << endl;
			delete[] parsed_buf;
		}
		delete[] buf;
		tf.close();
	}
}
void show_fam_elems(tree t, traverse_type tt, char* letter)
{
	queue q;
	switch (tt)
	{
	case prefix: q = prefix_traverse(t); break;
	case infix: q = infix_traverse(t); break;
	case postfix: q = postfix_traverse(t); break;
	case wide: q = wide_traverse(t); break;
	}
	auto curr = q.first;
	while (curr)
	{
		const auto v = curr->tree_node;
		if (!v) cout << "[-]";
		else if (v->v.surname == letter)
		{
			cout << (v->v.x) << (v->v.surname);
		}
		cout << " ";
		curr = curr->next;
	}
	cout << endl;
	clear(q);
}
void show_ball_elems(tree t, traverse_type tt, int ball)
{
	queue q;
	switch (tt)
	{
	case prefix: q = prefix_traverse(t); break;
	case infix: q = infix_traverse(t); break;
	case postfix: q = postfix_traverse(t); break;
	case wide: q = wide_traverse(t); break;
	}
	auto curr = q.first;
	while (curr)
	{
		const auto v = curr->tree_node;
		if (!v) cout << "[-]";
		else if (v->v.x == ball)
		{
			cout << (v->v.x) << (v->v.surname);
		}
		cout << " ";
		curr = curr->next;
	}
	cout << endl;
	clear(q);
}
