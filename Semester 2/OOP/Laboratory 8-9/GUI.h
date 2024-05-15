#pragma once

#include <qwidget.h>
#include "Account.h"
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qwindow.h>
#include <qlayout.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qlabel.h>
#include <QGridLayout>
#include "PopUp.h"
#include <qtimer.h>

class GUI : public QWidget
{
private:
	Administrator& admin;
	User& user;
	PopUp file_choice;
	QGridLayout* file_choice_layout = new QGridLayout;
	QPushButton* file_choice_button_1 = new QPushButton("TextFile");
	QPushButton* file_choice_button_2 = new QPushButton("CSVFile");
	QPushButton* file_choice_button_3 = new QPushButton("HTMLFile");
	QLabel* file_choice_label = new QLabel("Select Repository type");

	QGridLayout* main_window_layout = new QGridLayout{ this };
	QPushButton* main_window_button_1 = new QPushButton("Admin");
	QPushButton* main_window_button_2 = new QPushButton("User");
	QPushButton* main_window_button_3 = new QPushButton("Exit");
	QLabel* main_window_label = new QLabel("Select Account");

	PopUp admin_mode;
	QHBoxLayout* admin_mode_layout = new QHBoxLayout;
	QGridLayout* admin_mode_right_layout = new QGridLayout;
	QPushButton* admin_mode_button_1 = new QPushButton("Add");
	QPushButton* admin_mode_button_2 = new QPushButton("Delete");
	QPushButton* admin_mode_button_3 = new QPushButton("Update");
	QListWidget* Pets = new QListWidget;
	QLabel* admin_mode_label_1 = new QLabel("Breed");
	QLabel* admin_mode_label_2 = new QLabel("Name");
	QLabel* admin_mode_label_3 = new QLabel("Age");
	QLabel* admin_mode_label_4 = new QLabel("Photograph Link");
	QLineEdit* admin_mode_line_edit_1 = new QLineEdit;
	QLineEdit* admin_mode_line_edit_2 = new QLineEdit;
	QLineEdit* admin_mode_line_edit_3 = new QLineEdit;
	QLineEdit* admin_mode_line_edit_4 = new QLineEdit;

	PopUp update;
	QLabel* update_label_1 = new QLabel("New Name");
	QLabel* update_label_2 = new QLabel("New Age");
	QLabel* update_label_3 = new QLabel("New Photograph Link");
	QLineEdit* update_line_edit_1 = new QLineEdit;
	QLineEdit* update_line_edit_2 = new QLineEdit;
	QLineEdit* update_line_edit_3 = new QLineEdit;
	QGridLayout* update_layout = new QGridLayout;
	QPushButton* update_button = new QPushButton("Submit");

	PopUp user_mode;
	QListWidget* AdoptedPets = new QListWidget;
	QHBoxLayout* user_mode_layout = new QHBoxLayout;
	QGridLayout* user_mode_right_layout = new QGridLayout;
	QPushButton* user_mode_button_1 = new QPushButton("Adopt");
	QLabel* user_mode_label_1 = new QLabel("Breed");
	QLabel* user_mode_label_2 = new QLabel("Age");
	QLineEdit* user_mode_line_edit_1 = new QLineEdit;
	QLineEdit* user_mode_line_edit_2 = new QLineEdit;
	QPushButton* user_mode_button_2 = new QPushButton("Open");

	PopUp adoption;
	QListWidget* Current_Pet = new QListWidget;
	QVBoxLayout* adoption_layout = new QVBoxLayout;
	QPushButton* adoption_button_1 = new QPushButton("Adopt");
	QPushButton* adoption_button_2 = new QPushButton("Next");
	QPushButton* adoption_button_3 = new QPushButton("Exit");
	QGridLayout* adoption_grid_layout = new QGridLayout;
	int position = 0;
	std::vector<Dog> ToAdopt;

public:
	GUI(Administrator& admin, User& user);
private:
	void BuildGui();
	void SelectFile();
	void TextFileButtonHandle();
	void CSVFileButtonHandle();
	void HTMLFileButtonHandle();
	void Admin_Mode();
	void User_Mode();
	void Exit();
	void populate_admin();
	void Admin_Add();
	void Admin_Delete();
	void Admin_Update();
	void Update_Helper();
	void Adopt();
	void CaughtException(const std::exception& e);
	void AdoptCurrent();
	void NextPet();
	void ExitAdoption();
	void populate_user();
	void Open();
};