#include "GUI.h"

GUI::GUI(Administrator& admin, User& user) : admin{ admin }, user{ user }
{
	this->BuildGui();
	this->SelectFile();
	this->admin.ReadFromFile();
	this->populate_admin();
}

void GUI::BuildGui()
{
	//Window - File choice
	this->file_choice.setModal(true);
	this->file_choice.setLayout(this->file_choice_layout);
	this->file_choice_layout->addWidget(this->file_choice_label, 0, 1);
	this->file_choice_layout->addWidget(this->file_choice_button_1, 1, 0);
	this->file_choice_layout->addWidget(this->file_choice_button_2, 1, 1);
	this->file_choice_layout->addWidget(this->file_choice_button_3, 1, 2);
	connect(this->file_choice_button_1, &QPushButton::clicked, this, &GUI::TextFileButtonHandle);
	connect(this->file_choice_button_2, &QPushButton::clicked, this, &GUI::CSVFileButtonHandle);
	connect(this->file_choice_button_3, &QPushButton::clicked, this, &GUI::HTMLFileButtonHandle);
	this->file_choice.resize(300, 100);
	//Window - Main Program
	this->setLayout(this->main_window_layout);
	this->main_window_layout->addWidget(this->main_window_label, 0, 1);
	this->main_window_layout->addWidget(this->main_window_button_1, 1, 0);
	this->main_window_layout->addWidget(this->main_window_button_2, 1, 1);
	this->main_window_layout->addWidget(this->main_window_button_3, 1, 2);
	connect(this->main_window_button_1, &QPushButton::clicked, this, &GUI::Admin_Mode);
	connect(this->main_window_button_2, &QPushButton::clicked, this, &GUI::User_Mode);
	connect(this->main_window_button_3, &QPushButton::clicked, this, &GUI::Exit);
	//Window - Admin Mode
	this->admin_mode->setModal(true);
	connect(this->admin_mode, &PopUp::undoSignal, this, &GUI::Undo);
	connect(this->admin_mode, &PopUp::redoSignal, this, &GUI::Redo);
	this->admin_mode_layout->addWidget(this->Pets);
	this->admin_mode_right_layout->addWidget(this->admin_mode_label_1, 0, 0);
	this->admin_mode_right_layout->addWidget(this->admin_mode_label_2, 1, 0);
	this->admin_mode_right_layout->addWidget(this->admin_mode_label_3, 2, 0);
	this->admin_mode_right_layout->addWidget(this->admin_mode_label_4, 3, 0);
	this->admin_mode_right_layout->addWidget(this->admin_mode_line_edit_1, 0, 1, 1, 2);
	this->admin_mode_right_layout->addWidget(this->admin_mode_line_edit_2, 1, 1, 1, 2);
	this->admin_mode_right_layout->addWidget(this->admin_mode_line_edit_3, 2, 1, 1, 2);
	this->admin_mode_right_layout->addWidget(this->admin_mode_line_edit_4, 3, 1, 1, 2);
	this->admin_mode_right_layout->addWidget(this->admin_mode_button_1, 4, 0);
	this->admin_mode_right_layout->addWidget(this->admin_mode_button_2, 4, 1);
	this->admin_mode_right_layout->addWidget(this->admin_mode_button_3, 4, 2);
	this->admin_mode_right_layout->addWidget(this->admin_mode_button_4, 5, 0);
	this->admin_mode_right_layout->addWidget(this->admin_mode_button_5, 5, 2);
	this->admin_mode_layout->addLayout(this->admin_mode_right_layout);
	this->admin_mode->setLayout(this->admin_mode_layout);
	connect(this->admin_mode_button_1, &QPushButton::clicked, this, &GUI::Admin_Add);
	connect(this->admin_mode_button_2, &QPushButton::clicked, this, &GUI::Admin_Delete);
	connect(this->admin_mode_button_3, &QPushButton::clicked, this, &GUI::Admin_Update);
	connect(this->admin_mode_button_4, &QPushButton::clicked, this, &GUI::Undo);
	connect(this->admin_mode_button_5, &QPushButton::clicked, this, &GUI::Redo);
	//Window - User Mode
	this->user_mode.setModal(true);
	this->user_mode_layout->addWidget(this->AdoptedPets);
	this->user_mode_right_layout->addWidget(this->user_mode_label_1, 0, 0);
	this->user_mode_right_layout->addWidget(this->user_mode_label_2, 1, 0);
	this->user_mode_right_layout->addWidget(this->user_mode_line_edit_1, 0, 1);
	this->user_mode_right_layout->addWidget(this->user_mode_line_edit_2, 1, 1);
	this->user_mode_right_layout->addWidget(this->user_mode_button_1, 2, 0, 1, 1);
	this->user_mode_right_layout->addWidget(this->user_mode_button_2, 2, 1, 1, 1);
	this->user_mode_layout->addLayout(this->user_mode_right_layout);
	this->user_mode.setLayout(this->user_mode_layout);
	connect(this->user_mode_button_1, &QPushButton::clicked, this, &GUI::Adopt);
	connect(this->user_mode_button_2, &QPushButton::clicked, this, &GUI::Open);
	//Window - Admin/Update
	this->update_layout->addWidget(this->update_label_1, 0, 0);
	this->update_layout->addWidget(this->update_label_2, 1, 0);
	this->update_layout->addWidget(this->update_label_3, 2, 0);
	this->update_layout->addWidget(this->update_line_edit_1, 0, 1);
	this->update_layout->addWidget(this->update_line_edit_2, 1, 1);
	this->update_layout->addWidget(this->update_line_edit_3, 2, 1);
	this->update_layout->addWidget(this->update_button, 3, 0, 1, 2);
	connect(this->update_button, &QPushButton::clicked, this, &GUI::Update_Helper);
	this->update.setLayout(this->update_layout);
	this->update.setModal(true);
	this->update.resize(300, 300);
	//Window - Adoption Mode
	this->adoption.setModal(true);
	this->adoption_layout->addWidget(this->Current_Pet);
	this->adoption_grid_layout->addWidget(this->adoption_button_1, 0, 0);
	this->adoption_grid_layout->addWidget(this->adoption_button_2, 0, 1);
	this->adoption_grid_layout->addWidget(this->adoption_button_3, 0, 2);
	this->adoption_layout->addLayout(this->adoption_grid_layout);
	this->adoption.resize(400, 30);
	this->adoption.setLayout(this->adoption_layout);
	connect(this->adoption_button_1, &QPushButton::clicked, this, &GUI::AdoptCurrent);
	connect(this->adoption_button_2, &QPushButton::clicked, this, &GUI::NextPet);
	connect(this->adoption_button_3, &QPushButton::clicked, this, &GUI::ExitAdoption);
	//Window Main - Table view
	this->tableview.setModel(&this->mymodel);
	this->tableview.show();
	this->tableview.resize(350, 200);
	this->tableview.setColumnWidth(1, 200);
	this->tableview.setColumnWidth(0, 100);
	this->tableview.setColumnWidth(2, 50);
}

void GUI::SelectFile()
{
	this->file_choice.exec();
}

void GUI::TextFileButtonHandle()
{
	TextFileRepository* new_repo = new TextFileRepository("TextFileAdoption.txt");
	this->user.ChangeRepo(new_repo);
	this->file_choice.close();
}

void GUI::CSVFileButtonHandle()
{
	CSVRepository* new_repo = new CSVRepository("CSVRepository.csv");
	this->user.ChangeRepo(new_repo);
	this->file_choice.close();
}

void GUI::HTMLFileButtonHandle()
{
	HTMLRepository* new_repo = new HTMLRepository("HTMLRepository.html");
	this->user.ChangeRepo(new_repo);
	this->file_choice.close();
}

void GUI::Admin_Mode()
{
	this->admin_mode_line_edit_1->setText("");
	this->admin_mode_line_edit_2->setText("");
	this->admin_mode_line_edit_3->setText("");
	this->admin_mode_line_edit_4->setText("");
	this->admin_mode->exec();
}

void GUI::User_Mode()
{
	this->user_mode.exec();
}

void GUI::Exit()
{
	this->close();
}

void GUI::populate_admin()
{
	this->Pets->clear();
	for (Dog pet : this->admin.GetCopy())
	{
		this->Pets->addItem(QString::fromStdString(pet.GetName() + " | " + pet.GetBreed() + " | " + std::to_string(pet.GetAge())));
	}
}

void GUI::Admin_Add()
{
	QString breed = this->admin_mode_line_edit_1->text();
	QString name = this->admin_mode_line_edit_2->text();
	QString age = this->admin_mode_line_edit_3->text();
	QString photograph = this->admin_mode_line_edit_4->text();
	try
	{
		this->admin.Add(breed.toStdString(), name.toStdString(), std::stoi(age.toStdString()), photograph.toStdString());
		this->populate_admin();
	}
	catch (const std::exception& e)
	{
		this->CaughtException(e);
	}
}

void GUI::Admin_Delete()
{
	QString breed = this->admin_mode_line_edit_1->text();
	QString name = this->admin_mode_line_edit_2->text();
	QString age = this->admin_mode_line_edit_3->text();
	QString photograph = this->admin_mode_line_edit_4->text();
	try
	{
		this->admin.Delete(breed.toStdString(), name.toStdString(), std::stoi(age.toStdString()), photograph.toStdString());
		this->populate_admin();
	}
	catch (const std::exception& e)
	{
		this->CaughtException(e);
	}
}

void GUI::Admin_Update()
{
	this->update_line_edit_1->setText("");
	this->update_line_edit_2->setText("");
	this->update_line_edit_3->setText("");
	this->update.exec();
}

void GUI::Update_Helper()
{
	QString breed = this->admin_mode_line_edit_1->text();
	QString name = this->admin_mode_line_edit_2->text();
	QString age = this->admin_mode_line_edit_3->text();
	QString photograph = this->admin_mode_line_edit_4->text();
	QString new_name = this->update_line_edit_1->text();
	QString new_age = this->update_line_edit_2->text();
	QString new_photograph = this->update_line_edit_3->text();
	try
	{
		this->admin.Update(breed.toStdString(), name.toStdString(), std::stoi(age.toStdString()), photograph.toStdString(), new_name.toStdString(), std::stoi(new_age.toStdString()), new_photograph.toStdString());
		this->populate_admin();
	}
	catch (const std::exception& e)
	{
		this->CaughtException(e);
	}
	this->update.close();
}

void GUI::Adopt()
{
	QString breed = this->user_mode_line_edit_1->text();
	QString age = this->user_mode_line_edit_2->text();
	std::string std_string = breed.toStdString();
	std::string std_age = age.toStdString();
	this->position = 0;
	try
	{
		this->ToAdopt = this->user.Adopt(this->admin.GetCopy(), std_string, std_age);
	}
	catch (const std::exception& e)
	{
		this->CaughtException(e);
		return;
	}
	this->Current_Pet->clear();
	Dog Pet = this->ToAdopt[this->position];
	this->Current_Pet->addItem(QString::fromStdString(Pet.GetName() + " | " + Pet.GetBreed() + " | " + std::to_string(Pet.GetAge())));
	/*std::string link_start = "start " + this->ToAdopt[this->position].GetPhotograph();
	system(link_start.c_str());*/
	this->adoption.exec();
}

void GUI::CaughtException(const std::exception& e)
{
	PopUp exception_caught;
	QLabel* message = new QLabel(e.what());
	exception_caught.setModal(true);
	QGridLayout* layout = new QGridLayout;
	layout->addWidget(message);
	exception_caught.setLayout(layout);
	QTimer* timer = new QTimer(&exception_caught);
	timer->setSingleShot(true);
	connect(timer, &QTimer::timeout, &exception_caught, &QDialog::close);
	timer->start(2500);
	exception_caught.resize(100, 100);
	exception_caught.exec();
}

void GUI::AdoptCurrent()
{
	this->user.Add(this->ToAdopt[this->position]);
	this->mymodel.addDog(this->ToAdopt[this->position]);
	try
	{
		this->ToAdopt = this->user.Adopt(this->admin.GetCopy(), this->user_mode_line_edit_1->text().toStdString(), this->user_mode_line_edit_2->text().toStdString());
	}
	catch (const std::exception& e)
	{
		this->CaughtException(e);
		this->adoption.close();
	}
	this->NextPet();
	this->populate_user();
	this->user.WriteInFile();
}

void GUI::NextPet()
{
	this->position++;
	if (this->position > this->ToAdopt.size() - 1)
	{
		this->position = 0;
	}
	this->Current_Pet->clear();
	if (this->ToAdopt.size() == 0)
	{
		return;
	}
	this->Current_Pet->addItem(QString::fromStdString(this->ToAdopt[this->position].GetName() + " | " + this->ToAdopt[this->position].GetBreed() + " | " + std::to_string(this->ToAdopt[this->position].GetAge())));
	/*std::string link_start = "start " + this->ToAdopt[this->position].GetPhotograph();
	system(link_start.c_str());*/
}

void GUI::ExitAdoption()
{
	this->adoption.close();
}

void GUI::populate_user()
{
	this->AdoptedPets->clear();
	for (Dog pet : this->user.GetCopy())
	{
		this->AdoptedPets->addItem(QString::fromStdString(pet.GetName() + " | " + pet.GetBreed() + " | " + std::to_string(pet.GetAge())));
	}
}

void GUI::Open()
{
	this->user.Open();
}

void GUI::Undo()
{
	try
	{
		this->admin.Undo();
		this->populate_admin();
	}
	catch (const std::exception& e)
	{
		
	}
}

void GUI::Redo()
{
	try
	{
		this->admin.Redo();
		this->populate_admin();
	}
	catch (const std::exception& e)
	{
		
	}
}
