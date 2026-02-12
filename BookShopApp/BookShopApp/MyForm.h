#pragma once
#include "AddBookForm.h" // Підключення форми додавання

namespace BookShopApp {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Data::SqlClient;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent(); // Спочатку створюємо кнопки
            LoadData();            // Потім завантажуємо дані
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::DataGridView^ dataGridViewBooks;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Button^ btnExit;
        System::ComponentModel::Container^ components;

        // --- ФУНКЦІЯ ЗАВАНТАЖЕННЯ ДАНИХ ---
        void LoadData() {
           
            String^ connectionString = "Data Source=(localdb)\\MSSQLLocalDB;Initial Catalog=BookStore;Integrated Security=True";
            SqlConnection^ con = gcnew SqlConnection(connectionString);
            try {
                con->Open();
                SqlDataAdapter^ adapter = gcnew SqlDataAdapter("SELECT * FROM Books", con);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);

                // Перевірка, чи існує таблиця на формі перед заливкою
                if (dataGridViewBooks != nullptr) {
                    dataGridViewBooks->DataSource = dt;
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Помилка БД: " + ex->Message);
            }
        }

        // --- КНОПКИ ---
    private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {
        AddBookForm^ form = gcnew AddBookForm();
        form->ShowDialog();
        LoadData();
    }

    private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
        LoadData();
    }

    private: System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e) {
        Application::Exit();
    }

#pragma region Windows Form Designer generated code
           
           void InitializeComponent(void)
           {
               this->dataGridViewBooks = (gcnew System::Windows::Forms::DataGridView());
               this->btnAdd = (gcnew System::Windows::Forms::Button());
               this->btnRefresh = (gcnew System::Windows::Forms::Button());
               this->btnExit = (gcnew System::Windows::Forms::Button());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewBooks))->BeginInit();
               this->SuspendLayout();

               // 
               // dataGridViewBooks
               // 
               this->dataGridViewBooks->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->dataGridViewBooks->Location = System::Drawing::Point(12, 60); // Відступ зверху
               this->dataGridViewBooks->Name = L"dataGridViewBooks";
               this->dataGridViewBooks->Size = System::Drawing::Size(600, 300);
               this->dataGridViewBooks->TabIndex = 0;

               // 
               // btnAdd (Додати)
               // 
               this->btnAdd->Location = System::Drawing::Point(12, 12);
               this->btnAdd->Name = L"btnAdd";
               this->btnAdd->Size = System::Drawing::Size(100, 40);
               this->btnAdd->TabIndex = 1;
               this->btnAdd->Text = L"Додати";
               this->btnAdd->UseVisualStyleBackColor = true;
               this->btnAdd->Click += gcnew System::EventHandler(this, &MyForm::btnAdd_Click);

               // 
               // btnRefresh (Оновити)
               // 
               this->btnRefresh->Location = System::Drawing::Point(120, 12);
               this->btnRefresh->Name = L"btnRefresh";
               this->btnRefresh->Size = System::Drawing::Size(100, 40);
               this->btnRefresh->TabIndex = 2;
               this->btnRefresh->Text = L"Оновити";
               this->btnRefresh->UseVisualStyleBackColor = true;
               this->btnRefresh->Click += gcnew System::EventHandler(this, &MyForm::btnRefresh_Click);

               // 
               // btnExit (Вихід)
               // 
               this->btnExit->Location = System::Drawing::Point(510, 12);
               this->btnExit->Name = L"btnExit";
               this->btnExit->Size = System::Drawing::Size(100, 40);
               this->btnExit->TabIndex = 3;
               this->btnExit->Text = L"Вихід";
               this->btnExit->UseVisualStyleBackColor = true;
               this->btnExit->Click += gcnew System::EventHandler(this, &MyForm::btnExit_Click);

               // 
               // MyForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(640, 400);
               this->Controls->Add(this->btnExit);
               this->Controls->Add(this->btnRefresh);
               this->Controls->Add(this->btnAdd);
               this->Controls->Add(this->dataGridViewBooks);
               this->Name = L"MyForm";
               this->Text = L"Книжковий магазин";
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewBooks))->EndInit();
               this->ResumeLayout(false);

           }
#pragma endregion
    };
}