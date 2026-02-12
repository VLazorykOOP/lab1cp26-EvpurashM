#pragma once

namespace BookShopApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient; // Підключення до БД

	public ref class AddBookForm : public System::Windows::Forms::Form
	{
	public:
		AddBookForm(void)
		{
			InitializeComponent();
		}

	protected:
		~AddBookForm()
		{
			if (components)
			{
				delete components;
			}
		}

		// Оголошуємо змінні для полів (щоб вони точно існували)
	private: System::Windows::Forms::TextBox^ textBox1; // Автор
	private: System::Windows::Forms::TextBox^ textBox2; // Назва
	private: System::Windows::Forms::TextBox^ textBox3; // Видавництво
	private: System::Windows::Forms::TextBox^ textBox4; // Сторінки
	private: System::Windows::Forms::TextBox^ textBox5; // Жанр
	private: System::Windows::Forms::TextBox^ textBox6; // Ціна
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ button1; // Кнопка Зберегти

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			// Створюємо елементи
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();

			// --- Налаштування розташування (Дизайн) ---

			// 1. Автор
			this->label1->Text = L"Автор:";
			this->label1->Location = System::Drawing::Point(20, 20);
			this->label1->AutoSize = true;

			this->textBox1->Location = System::Drawing::Point(120, 20);
			this->textBox1->Size = System::Drawing::Size(200, 22);

			// 2. Назва
			this->label2->Text = L"Назва:";
			this->label2->Location = System::Drawing::Point(20, 60);
			this->label2->AutoSize = true;

			this->textBox2->Location = System::Drawing::Point(120, 60);
			this->textBox2->Size = System::Drawing::Size(200, 22);

			// 3. Видавництво
			this->label3->Text = L"Видавництво:";
			this->label3->Location = System::Drawing::Point(20, 100);
			this->label3->AutoSize = true;

			this->textBox3->Location = System::Drawing::Point(120, 100);
			this->textBox3->Size = System::Drawing::Size(200, 22);

			// 4. Сторінки
			this->label4->Text = L"Сторінки:";
			this->label4->Location = System::Drawing::Point(20, 140);
			this->label4->AutoSize = true;

			this->textBox4->Location = System::Drawing::Point(120, 140);
			this->textBox4->Size = System::Drawing::Size(100, 22);

			// 5. Жанр
			this->label5->Text = L"Жанр:";
			this->label5->Location = System::Drawing::Point(20, 180);
			this->label5->AutoSize = true;

			this->textBox5->Location = System::Drawing::Point(120, 180);
			this->textBox5->Size = System::Drawing::Size(200, 22);

			// 6. Ціна
			this->label6->Text = L"Ціна:";
			this->label6->Location = System::Drawing::Point(20, 220);
			this->label6->AutoSize = true;

			this->textBox6->Location = System::Drawing::Point(120, 220);
			this->textBox6->Size = System::Drawing::Size(100, 22);

			// Кнопка ЗБЕРЕГТИ
			this->button1->Text = L"Зберегти";
			this->button1->Location = System::Drawing::Point(120, 270);
			this->button1->Size = System::Drawing::Size(100, 40);
			this->button1->UseVisualStyleBackColor = true;
			// Прив'язуємо подію кліку
			this->button1->Click += gcnew System::EventHandler(this, &AddBookForm::button1_Click);

			// Додаємо все на форму
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);

			// Налаштування самої форми
			this->ClientSize = System::Drawing::Size(400, 350);
			this->Text = L"Додати книгу";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

		// --- ЛОГІКА ЗБЕРЕЖЕННЯ ---
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ connectionString = "Data Source=(localdb)\\MSSQLLocalDB;Initial Catalog=BookStore;Integrated Security=True";
		SqlConnection^ con = gcnew SqlConnection(connectionString);

		try {
			con->Open();
			String^ sql = "INSERT INTO Books (Authors, Title, Publisher, PageCount, Genre, Price) VALUES (@auth, @title, @pub, @page, @gen, @price)";
			SqlCommand^ cmd = gcnew SqlCommand(sql, con);

			
			if (textBox1->Text == "") {
				MessageBox::Show("Введіть хоча б автора!");
				return;
			}

			cmd->Parameters->AddWithValue("@auth", textBox1->Text);
			cmd->Parameters->AddWithValue("@title", textBox2->Text);
			cmd->Parameters->AddWithValue("@pub", textBox3->Text);
			cmd->Parameters->AddWithValue("@page", Convert::ToInt32(textBox4->Text));
			cmd->Parameters->AddWithValue("@gen", textBox5->Text);
			cmd->Parameters->AddWithValue("@price", Convert::ToDecimal(textBox6->Text));

			cmd->ExecuteNonQuery();
			MessageBox::Show("Успішно додано!");
			this->Close();
		}
		catch (Exception^ ex) {
			MessageBox::Show("Помилка! Перевірте, чи ввели ви числа у поля 'Сторінки' та 'Ціна'.\n" + ex->Message);
		}
		finally {
			con->Close();
		}
	}
	};
}