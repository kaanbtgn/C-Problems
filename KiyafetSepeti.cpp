/*
402509 - Ömer Faruk TAŞKIN
402514 - Kaan BİTGİN
402513 - Berat AK
*/


#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>  
#include <vector>
#include <regex>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <array>
#include <sstream>
#include <filesystem>
#include <set>
#include <iomanip>
#include <ctime>
#include<tuple>

using namespace std;



//Enums
enum UserRole { admin, customer, courier };

//Static Variables
static string PropertyDelimeterStr = "§";
static string UserDatasPath = "users.txt";
static string ProductDatasPath = "products.txt";
static string SuggestionDatasPath = "suggestions.txt";
static string OrderDatasPath = "orders.txt";
static string OrderProductDatasPath = "orderproducts.txt";
static char PropertyDelimeterChr = '§';
static vector<string> Districts{ "Ortahisar", "Akcaabat", "Vakfikebir", "Besikduzu", "Yomra", "Arsin", "Arakli" };
static vector<int> DistrictDistances{ 35,50,90,110,55,70,100 };
static vector<string> Categories{ "Elbise","Tisort","Pantolon","Gomlek","Etek","Ayakkabi" };
static vector<string> Sizes{ "XS","S","M","L","XL","XXL" };

//Static Methods
/**
* @name ConvertStrToInt
* @param [in] i [\b int]
* @param [in] s [\b char]
* @retval [\b bool]
* This method converts string to integer.
**/
static bool ConvertStrToInt(int& i, char const* s)
{
	char c;
	std::stringstream ss(s);
	ss >> i;
	if (ss.fail() || ss.get(c)) {
		// not an integer
		return false;
	}
	return true;
}

/**
* @name ConvertStrToDouble
* @param [in] i [\b double]
* @param [in] s [\b char]
* @retval [\b bool]
* This method converts string to double.
**/
static bool ConvertStrToDouble(double& i, char const* s) {
	char c;
	std::stringstream ss(s);
	ss >> i;
	if (ss.fail() || ss.get(c)) {
		// not an double
		return false;
	}
	return true;
}

/**
* @name CreateGuid
* @retval [\b string]
* This method creates guid.
**/
static string CreateGuid() {
	std::string result{};
	GUID guid;

	if (S_OK == CoCreateGuid(&guid))
	{
		std::array<char, 36> buffer{};   //32 characters of guid + 4 '-' in-between

		snprintf(buffer.data(), buffer.size(), "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
			guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		result = std::string(buffer.data());
	}

	return result;
}

/**
* @name SplitStringWithDelimeter
* @param [in] str [\b string]
* @retval [\b vector]
* This method splits input accoring to special delimeter.
**/
static vector<string> SplitStringWithDelimeter(string str) {
	std::vector<std::string>   result;

	std::stringstream  data(str);

	std::string line;
	while (std::getline(data, line, PropertyDelimeterChr))
	{
		result.push_back(line); // Note: You may get a couple of blank lines
		// When multiple underscores are beside each other.
	}
	return result;
}

/**
* @name rtrim
* @param [in] s [\b string]
* @retval [\b void]
* This method deletes which whitespaces in inputs left.
**/
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

/**
* @name rtrim
* @param [in] s [\b string]
* @retval [\b void]
* This method deletes which whitespaces in inputs right.
**/
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

/**
* @name trim
* @param [in] s [\b string]
* @retval [\b void]
* This method deletes which whitespaces in input.
**/
static inline void trim(std::string& s) {
	rtrim(s);
	ltrim(s);
}

//Classes
class SuggestionAndComplaint {
public:
	string Text;
	string Username;
	string GetLine() {
		return Username + PropertyDelimeterStr + Text;
	}
	void Add() {
		ofstream foutput;
		foutput.open(SuggestionDatasPath, ios::app);
		foutput << this->GetLine() << endl;
		foutput.close();
	}
};
class kiyafet {
public:
	string guid;
	string kategori;
	string kiyafet_adi;
	double fiyat = NULL;
	string boyut;
	string renk;
	void Add() {
		ofstream foutput;
		this->guid = CreateGuid();
		foutput.open(ProductDatasPath, ios::app);
		foutput << this->GetLine() << endl;
		foutput.close();
	}
	string GetLine() {
		return guid + PropertyDelimeterStr + kategori + PropertyDelimeterStr + kiyafet_adi + PropertyDelimeterStr + boyut + PropertyDelimeterStr + renk + PropertyDelimeterStr + to_string(fiyat);
	}
};
class zaman {
public:
	zaman()
	{

	}
	zaman(int _saat, int _dakika)
	{
		saat = _saat;
		dakika = _dakika;
	}
	int dakika;
	int saat;
	zaman operator+(zaman const& obj) {
		return Sum(obj);
	}
	bool operator>(zaman const& obj) {
		return  this->saat * 60 + this->dakika > obj.saat * 60 + obj.dakika;
	}
	bool operator<(zaman const& obj) {
		return this->saat * 60 + this->dakika < obj.saat * 60 + obj.dakika;
	}
	zaman operator+(int const& obj) {
		zaman inputData;
		inputData.saat = obj / 60;
		inputData.dakika = obj % 60;
		return Sum(inputData);
	}
private:
	zaman Sum(zaman const& obj) {
		zaman returnData;
		int minute = dakika + obj.dakika;
		returnData.saat = saat + obj.saat + minute / 60;
		returnData.dakika = minute % 60;
		return returnData;
	}
};
class kisi {
public:
	string guid;
	string ad_soyad;
	string tel_no;
	UserRole role;
};
class kullanici :public kisi {
public:
	kullanici()
	{
		role = UserRole::customer;
	}
	string kullanici_adi;
	string eposta;
	string adres_ilce;
	string sifre;
	string indirim_kodu;
	string dtarihi;
	double DiscountAmount;
	string GetLine() {
		return guid + PropertyDelimeterStr + "1" + PropertyDelimeterStr + ad_soyad + PropertyDelimeterStr + kullanici_adi + PropertyDelimeterStr + sifre + PropertyDelimeterStr + eposta + PropertyDelimeterStr + dtarihi + PropertyDelimeterStr + indirim_kodu + PropertyDelimeterStr + adres_ilce + PropertyDelimeterStr + tel_no + PropertyDelimeterStr + to_string(DiscountAmount);
	}
	void Add() {
		ofstream foutput;
		this->guid = CreateGuid();
		foutput.open(UserDatasPath, ios::app);
		foutput << this->GetLine() << endl;
		foutput.close();
	}
};
class yonetici :public kisi {
public:
	yonetici()
	{
		role = UserRole::admin;
	}
	string sifre;
};
class kurye :public kisi {
public:
	kurye()
	{
		role = UserRole::courier;
	}
	int* siparis_numaralari;
	zaman* dagitim_bitisler;
	int size_siparis_numaralari;
	int size_dagitim_bitisler;
	string GetLine() {
		return guid + PropertyDelimeterStr + "2" + PropertyDelimeterStr + ad_soyad + PropertyDelimeterStr + tel_no;
	}
	void Add() {
		ofstream foutput;
		this->guid = CreateGuid();
		foutput.open(UserDatasPath, ios::app);
		foutput << this->GetLine() << endl;
		foutput.close();
	}
};
class Order {
public:
	int Id;
	vector<string> ProductGuids;
	vector<kiyafet> Products;
	string UserGuid;
	kullanici User;
	string CourierGuid;
	zaman OrderDate;
	string Address;
	zaman OrderDeliveryDate;
	double TotalOrderPrice;
	void Add() {
		this->Id = GetLastId() + 1;
		AddOrderProdIds();
		ofstream foutput;
		foutput.open(OrderDatasPath, ios::app);
		foutput << this->GetLine() << endl;
		foutput.close();
	};

	string GetLine() {
		return to_string(Id) + PropertyDelimeterStr + CourierGuid + PropertyDelimeterStr + UserGuid + PropertyDelimeterStr + Address + PropertyDelimeterStr + to_string(OrderDate.saat) + PropertyDelimeterStr + to_string(OrderDate.dakika) + PropertyDelimeterStr + to_string(OrderDeliveryDate.saat) + PropertyDelimeterStr + to_string(OrderDeliveryDate.dakika) + PropertyDelimeterStr + to_string(TotalOrderPrice);
	};
private:
	int GetLastId() {
		int id = 0;
		ifstream file(OrderDatasPath);
		string str;
		while (getline(file, str))
		{
			vector<string> properties = SplitStringWithDelimeter(str);
			ConvertStrToInt(id, properties[0].c_str());
		}
		return id;
	}
	void AddOrderProdIds() {
		for (int i = 0; i < Products.size(); i++)
		{
			string line = to_string(this->Id) + PropertyDelimeterStr + Products[i].guid;
			ofstream foutput;
			foutput.open(OrderProductDatasPath, ios::app);
			foutput << line << endl;
			foutput.close();
		}
	}
};

//Variables
kullanici RegisteredUser;

//Methods

/**
* @name Update
* @param [in] obj [\b T]
* @retval [\b void]
* This method updates input object in system.
**/
template <typename T>
void Update(T obj) {
	string id;
	string originalFileName;
	ifstream originalFile;
	ofstream tempFile;
	string line;
	string insertLine;
	tempFile.open("temp.txt", ios::out);

	if (typeid(obj) == typeid(kullanici)) {
		kullanici user = (kullanici)obj;

		id = user.guid;
		originalFile.open(UserDatasPath);
		originalFileName = UserDatasPath;
		insertLine = user.GetLine();
	}

	while (getline(originalFile, line))
	{
		if (line.find(id) != std::string::npos) {
			line = insertLine;
		}
		tempFile << line << endl;
	}
	originalFile.close();
	tempFile.close();
	remove(originalFileName.c_str());
	rename("temp.txt", originalFileName.c_str());
}

/**
* @name GetAllProducts
* @retval [\b vector]
* This method returns all products in system.
**/
vector<kiyafet> GetAllProducts() {
	vector<kiyafet> returnData;
	ifstream file;
	string line;
	file.open(ProductDatasPath, ios::out);
	while (getline(file, line))
	{
		kiyafet temp;
		vector<string>properties = SplitStringWithDelimeter(line);
		temp.guid = properties[0];
		temp.kategori = properties[1];
		temp.kiyafet_adi = properties[2];
		temp.boyut = properties[3];
		temp.renk = properties[4];
		ConvertStrToDouble(temp.fiyat, properties[5].c_str());
		returnData.push_back(temp);
	}
	return returnData;
}

/**
* @name GetProductWithGuid
* @retval [\b vector]
* This method returns product which pair with input guid.
**/
kiyafet GetProductWithGuid(string guid) {
	vector<kiyafet> allProducts = GetAllProducts();
	for (int i = 0; i < allProducts.size(); i++)
	{
		if (allProducts[i].guid == guid)
			return allProducts[i];
	}
}

/**
* @name GetProductNamesGroupped
* @param [in] v [\b vector]
* @retval [\b set]
* This method groups items by name.
**/
set<string> GetProductNamesGroupped(vector<kiyafet> v)
{
	// Declaring the set
	set<string> s;

	// Traverse the Vector
	for (int i = 0; i < v.size(); i++)
	{
		// Insert each element
		// into the Set
		s.insert(v[i].kiyafet_adi);
	}

	// Return the resultant Set
	return s;
}

/**
* @name GetProductSizesGroupped
* @param [in] v [\b vector]
* @retval [\b set]
* This method groups items by size.
**/
set<string> GetProductSizesGroupped(vector<kiyafet> v)
{
	// Declaring the set
	set<string> s;

	// Traverse the Vector
	for (int i = 0; i < v.size(); i++)
	{
		// Insert each element
		// into the Set
		s.insert(v[i].boyut);
	}

	// Return the resultant Set
	return s;
}

/**
* @name GetProductColoursGroupped
* @param [in] v [\b vector]
* @retval [\b set]
* This method groups items by color.
**/
set<string> GetProductColoursGroupped(vector<kiyafet> v)
{
	// Declaring the set
	set<string> s;

	// Traverse the Vector
	for (int i = 0; i < v.size(); i++)
	{
		// Insert each element
		// into the Set
		s.insert(v[i].renk);
	}

	// Return the resultant Set
	return s;
}

/**
* @name GetAllCustomers
* @retval [\b vector]
* This method returns all customers in system.
**/
vector<kullanici> GetAllCustomers() {
	vector<kullanici> returnData;
	ifstream file(UserDatasPath);
	string line;
	while (getline(file, line))
	{
		kullanici temp;
		vector<string>properties = SplitStringWithDelimeter(line);
		if (properties[1] != "1")
			continue;
		temp.guid = properties[0];
		temp.role = UserRole::customer;
		temp.ad_soyad = properties[2];
		temp.kullanici_adi = properties[3];
		temp.sifre = properties[4];
		temp.eposta = properties[5];
		temp.dtarihi = properties[6];
		temp.indirim_kodu = properties[7];
		temp.adres_ilce = properties[8];
		temp.tel_no = properties[9];
		ConvertStrToDouble(temp.DiscountAmount, properties[10].c_str());
		returnData.push_back(temp);
	}
	return returnData;
}

/**
* @name GetCustomerWithGuid
* @param [in] guid [\b string]
* @retval [\b kullanici]
* This method returns customer which pair with input guid.
**/
kullanici GetCustomerWithGuid(string guid) {
	vector<kullanici> allCustomers = GetAllCustomers();
	for (int i = 0; i < allCustomers.size(); i++)
	{
		if (allCustomers[i].guid == guid)
			return allCustomers[i];
	}
}

/**
* @name GetAllSuggestions
* @retval [\b vector]
* This method returns all suggestions in system.
**/
vector<SuggestionAndComplaint> GetAllSuggestions() {
	vector<SuggestionAndComplaint> returnData;
	ifstream file(SuggestionDatasPath);
	string str;
	while (getline(file, str))
	{
		vector<string> properties = SplitStringWithDelimeter(str);
		SuggestionAndComplaint temp;
		temp.Username = properties[0];
		temp.Text = properties[1];
		returnData.push_back(temp);
	}
	return returnData;
}

/**
* @name GetOrderProductsId
* @param [in] orderId [\b int]
* @retval [\b vector]
* This method returns orders products ids.
**/
vector<string>GetOrderProductsId(int orderId)
{
	vector<string> returnData;
	ifstream file(OrderProductDatasPath);
	string line;
	while (getline(file, line))
	{
		int id;
		vector<string>properties = SplitStringWithDelimeter(line);
		ConvertStrToInt(id, properties[0].c_str());
		if (id == orderId)
			returnData.push_back(properties[1]);
	}
	return returnData;
}

/**
* @name GetAllOrders
* @retval [\b vector]
* This method returns all orders in system.
**/
vector<Order> GetAllOrders() {
	vector<Order> returnData;
	ifstream file(OrderDatasPath);
	string line;
	while (getline(file, line))
	{
		Order temp;
		vector<string>properties = SplitStringWithDelimeter(line);
		ConvertStrToInt(temp.Id, properties[0].c_str());
		temp.ProductGuids = GetOrderProductsId(temp.Id);
		for (int i = 0; i < temp.ProductGuids.size(); i++)
		{
			temp.Products.push_back(GetProductWithGuid(temp.ProductGuids[i]));
		}
		temp.CourierGuid = properties[1];
		temp.UserGuid = properties[2];
		temp.User = GetCustomerWithGuid(temp.UserGuid);
		temp.Address = properties[3];
		ConvertStrToInt(temp.OrderDate.saat, properties[4].c_str());
		ConvertStrToInt(temp.OrderDate.dakika, properties[5].c_str());
		ConvertStrToInt(temp.OrderDeliveryDate.saat, properties[6].c_str());
		ConvertStrToInt(temp.OrderDeliveryDate.dakika, properties[7].c_str());
		ConvertStrToDouble(temp.TotalOrderPrice, properties[8].c_str());
		returnData.push_back(temp);
	}
	return returnData;
}

/**
* @name GetUsersOrdersWithGuid
* @param [in] guid [\b string]
* @retval [\b vector]
* This method returns the users orders.
**/
vector<Order> GetUsersOrdersWithGuid(string guid) {
	vector<Order> returnData;
	vector<Order> allOrders = GetAllOrders();
	for (int i = 0; i < allOrders.size(); i++)
	{
		if (allOrders[i].UserGuid == guid)
			returnData.push_back(allOrders[i]);
	}
	return returnData;
}

/**
* @name GetCourierOrdersWithGuid
* @param [in] guid [\b string]
* @retval [\b vector]
* This method returns the courier of the order.
**/
vector<Order>GetCourierOrdersWithGuid(string guid) {
	vector<Order> returnData;
	vector<Order> allOrders = GetAllOrders();
	for (int i = 0; i < allOrders.size(); i++)
	{
		if (allOrders[i].CourierGuid == guid)
			returnData.push_back(allOrders[i]);
	}
	return returnData;
}

/**
* @name GetCurrentDesktopTime
* @retval [\b zaman]
* This method returns current time.
**/
zaman GetCurrentDesktopTime() {
	zaman returnData;
	time_t currentTime;
	struct tm* localTime;

	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time

	returnData.saat = localTime->tm_hour;
	returnData.dakika = localTime->tm_min;
	return returnData;
}

/**
* @name GetAllCouriers
* @retval [\b vector]
* This method returns all couriers in system.
**/
vector<kurye> GetAllCouriers() {
	vector<kurye> returnData;
	std::ifstream file(UserDatasPath);
	std::string str;
	while (std::getline(file, str))
	{
		vector<string> properties = SplitStringWithDelimeter(str);
		if (properties[1] != "2")
			continue;
		kurye tempCourier;
		vector<Order> tempCourierOrders;
		tempCourier.guid = properties[0];
		tempCourier.role = UserRole::courier;
		tempCourier.ad_soyad = properties[2];
		tempCourier.tel_no = properties[3];
		tempCourierOrders = GetCourierOrdersWithGuid(tempCourier.guid);
		tempCourier.siparis_numaralari = new int[tempCourierOrders.size()];
		tempCourier.dagitim_bitisler = new zaman[tempCourierOrders.size()];
		tempCourier.size_dagitim_bitisler = tempCourierOrders.size();
		tempCourier.size_siparis_numaralari = tempCourierOrders.size();
		for (int i = 0; i < tempCourierOrders.size(); i++)
		{
			tempCourier.siparis_numaralari[i] = tempCourierOrders[i].Id;
			tempCourier.dagitim_bitisler[i] = tempCourierOrders[i].OrderDeliveryDate;
		}
		returnData.push_back(tempCourier);
	}
	return returnData;
}

/**
* @name IsUsernameUsedBefore
* @param [in] username [\b string]
* @retval [\b bool]
* This method checks is username used before.
**/
bool IsUsernameUsedBefore(string username) {
	std::ifstream file(UserDatasPath);
	std::string str;
	while (std::getline(file, str))
	{
		vector<string> properties = SplitStringWithDelimeter(str);
		if (properties[1] == "1" && properties[3] == username)
			return true;
	}
	return false;
}

/**
* @name CheckValidCredentials
* @param [in] username [\b string]
* @param [in] pass [\b string]
* @param [in] role [\b UserRole]
* @retval [\b bool]
* This method checks user credentials by user role and returning true if valid.
**/
bool CheckValidCredentials(string username, string pass, UserRole role) {
	std::ifstream file(UserDatasPath);
	std::string str;
	while (std::getline(file, str))
	{
		vector<string> properties = SplitStringWithDelimeter(str);
		if (role == UserRole::admin && properties[1] == "0" && properties[3] == pass)
			return true;
		else if (role == UserRole::customer && properties[1] == "1" && properties[3] == username && properties[4] == pass)
		{
			RegisteredUser.guid = properties[0];
			RegisteredUser.role = UserRole::customer;
			RegisteredUser.ad_soyad = properties[2];
			RegisteredUser.kullanici_adi = properties[3];
			RegisteredUser.sifre = properties[4];
			RegisteredUser.eposta = properties[5];
			RegisteredUser.dtarihi = properties[6];
			RegisteredUser.indirim_kodu = properties[7];
			RegisteredUser.adres_ilce = properties[8];
			RegisteredUser.tel_no = properties[9];
			ConvertStrToDouble(RegisteredUser.DiscountAmount, properties[10].c_str());
			return true;
		}
	}
	return false;
}

/**
* @name GetDistanceOfDistrict
* @param [in] district [\b string]
* @retval [\b int]
* This method returns distance in minutes of destination address.
**/
int GetDistanceOfDistrict(string district) {
	for (int i = 0; i < Districts.size(); i++)
		if (Districts[i] == district)
			return DistrictDistances[i];
}

/**
* @name SelectOptimalCourier
* @param [in] district [\b string]
* @retval [\b tuple]
* This method selects optimal courier and calculating optimal time for the destination address.
**/
tuple<kurye, zaman> SelectOptimalCourier(string district) {
	int distanceOfDistrict = GetDistanceOfDistrict(district);
	kurye selectedCourier;
	zaman deliveryTime(999, 59);
	vector<kurye> allCouriers = GetAllCouriers();
	for (int i = 0; i < allCouriers.size(); i++)
	{
		zaman lastDeliveryTime = GetCurrentDesktopTime();
		for (int j = 0; j < allCouriers[i].size_dagitim_bitisler; j++)
		{
			if (lastDeliveryTime < allCouriers[i].dagitim_bitisler[j])
				lastDeliveryTime = allCouriers[i].dagitim_bitisler[j];
		}

		if (lastDeliveryTime + distanceOfDistrict < deliveryTime) {
			selectedCourier = allCouriers[i];
			deliveryTime = lastDeliveryTime + distanceOfDistrict;
		}
	}
	return std::make_tuple(selectedCourier, deliveryTime);
}

/**
* @name FileExist
* @param [in] fileName [\b string]
* @retval [\b bool]
* This method checks if the file exist.
**/
bool FileExist(string fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

/**
* @name CreateFiles
* @retval [\b void]
* This method creats text files which non created.
**/
void CreateFiles() {
	if (!FileExist(UserDatasPath))
	{
		std::ofstream outfile(UserDatasPath);
		outfile << "fe792d94-a7c8-4c16-8df7-ec28a609ab3§0§admin§@dmiN147§5078251535" << endl;
	}
	if (!FileExist(SuggestionDatasPath))
		std::ofstream outfile(SuggestionDatasPath);
	if (!FileExist(ProductDatasPath))
		std::ofstream outfile(ProductDatasPath);
	if (!FileExist(OrderDatasPath))
		std::ofstream outfile(OrderDatasPath);
	if (!FileExist(OrderProductDatasPath))
		std::ofstream outfile(OrderProductDatasPath);
}

/**
* @name ClearConsole
* @retval [\b void]
* This method clears console.
**/
void ClearConsole() {
	system("cls");
}

/**
* @name PrintToConsole
* @param [in] s [\b string]
* @param [in] withNewLine [\b bool]
* @param [in] width [\b int]
* @retval [\b void]
* This method allows to print string where you want.
**/
void PrintToConsole(string s, bool withNewLine = true, int width = -1)
{
	if (width > 0)
		cout << std::left << std::setw(width) << s;
	else
		cout << s;

	if (withNewLine)
		cout << endl;
}

/**
* @name GetInput
* @param [in] isHide [\b bool]
* @retval [\b string]
* This method gets input from console.
**/
string GetInput(bool isHide = false) {
	string input;
	if (isHide)
	{
		char ch;
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == 8) {
				// backspace was pressed
				if (input.length()) {
					cout << "\b \b";
					input.pop_back();
				}
				ch = _getch();
				continue;
			}
			//character 13 is enter
			input.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		cout << endl;
	}
	else
		getline(cin, input);
	trim(input);
	return input;
}

/**
* @name CheckWithRegex
* @param [in] pattern [\b string]
* @param [in] data [\b string]
* @retval [\b bool]
* This method checks data with regex.
**/
bool CheckWithRegex(string pattern, string data) {
	const regex integer_expr(pattern);
	return regex_match(data, integer_expr);
}

/**
* @name PrintOrderProducts
* @param [in] order [\b Order]
* @retval [\b void]
* This method prints orders products to console.
**/
void PrintOrderProducts(Order order) {
	PrintToConsole("Kategori", false, 15);
	PrintToConsole("Urun Adi", false, 40);
	PrintToConsole("Urun Rengi", false, 15);
	PrintToConsole("Urun Boyutu", false, 15);
	PrintToConsole("Fiyat", true, 10);
	PrintToConsole("-----------------------------------------------------------------------------------------------");
	for (int i = 0; i < order.Products.size(); i++)
	{
		kiyafet temp = order.Products[i];
		PrintToConsole(temp.kategori, false, 15);
		PrintToConsole(temp.kiyafet_adi, false, 40);
		PrintToConsole(temp.renk, false, 15);
		PrintToConsole(temp.boyut, false, 15);
		PrintToConsole(to_string(temp.fiyat), true, 10);
	}
	PrintToConsole("", false, 71);
	PrintToConsole("Toplam Fiyat: " + to_string(order.TotalOrderPrice), true);
}

/**
* @name PrintUserOrders
* @retval [\b void]
* This method prints users orders to console.
**/
void PrintUserOrders() {
	ClearConsole();
	Order selectedOrder;
	while (selectedOrder.Id == 0)
	{
		PrintToConsole("Ayrintilarini gormek istediginiz siparisi seciniz. Ust menuye donmek icin '0' giriniz.\n");
		vector<Order> orders = GetUsersOrdersWithGuid(RegisteredUser.guid);
		PrintToConsole("Olusturma Tarihi", false, 20);
		PrintToConsole("Teslim Tarihi", false, 20);
		PrintToConsole("Teslimat Adresi", false, 20);
		PrintToConsole("Toplam Tutar", false, 15);
		PrintToConsole("Durum", true, 20);
		PrintToConsole("-----------------------------------------------------------------------------------------------");
		for (int i = 0; i < orders.size(); i++)
		{
			Order order = orders[i];
			zaman currentTime = GetCurrentDesktopTime();
			PrintToConsole(to_string(i + 1) + "- ", false);
			PrintToConsole(to_string(order.OrderDate.saat) + ":" + to_string(order.OrderDate.dakika), false, 20);
			PrintToConsole(to_string(order.OrderDeliveryDate.saat) + ":" + to_string(order.OrderDeliveryDate.dakika), false, 20);
			PrintToConsole(order.Address, false, 20);
			PrintToConsole(to_string(order.TotalOrderPrice), false, 15);
			if (order.OrderDeliveryDate > currentTime)
				PrintToConsole("Teslim edilecek", true, 15);
			else
				PrintToConsole("Teslim edildi", true, 15);
		}
		string data = GetInput();
		if (data == "0")
			return;
		int integerData;

		if (ConvertStrToInt(integerData, data.c_str()))
		{
			if (integerData >= 1 && integerData <= orders.size())
				selectedOrder = orders[integerData - 1];
			else {
				PrintToConsole("Lutfen gecerli bir siparis seciniz.");
			}
		}
		else
			PrintToConsole("Lutfen gecerli bir siparis seciniz.");
	}

	PrintToConsole("Siparisinizdeki urunler asagidaki gibidir. Ust menuye donmek icin entera basiniz.");
	PrintOrderProducts(selectedOrder);
	GetInput();
}

/**
* @name ChangeUserPassword
* @retval [\b void]
* This method gets new password from user and changing password.
**/
void ChangeUserPassword() {
	ClearConsole();
	PrintToConsole("Sifreniz en az 1 buyuk karakter, en az 1 kucuk karakter, en az 1 ozel karakter, en az 1 adet sayi icermeli, en az 8 karakter uzunlugunda ve en fazla 15 karakter uzunlugunda olmalidir. Ust menuye donmek icin '0' yazin.");
	string passInput;
	while (passInput != "0")
	{
		PrintToConsole("Yeni sifre: ");
		passInput = GetInput(true);

		/*
		^ Start anchor
		(?=.*[A-Z].*[A-Z])        Ensure string has two uppercase letters.
		(?=.*[!@#$&*])            Ensure string has one special case letter.
		(?=.*[0-9])               Ensure string has one digits.
		(?=.*[a-z].*[a-z])        Ensure string has two lowercase letters.
		.{8}                      Ensure string is of length 8.
		$                         End anchor.
		*/

		if (CheckWithRegex("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[\\W\\_])[a-zA-Z0-9\\W\\_]{8,15}$", passInput))
		{
			RegisteredUser.sifre = passInput;
			Update(RegisteredUser);
			PrintToConsole("Sifreniz basariyla degistirildi. Devam etmek icin entera basin.");
			GetInput();
			return;
		}
		else
			PrintToConsole("Lutfen gecerli bir sifre giriniz.");
	}
}

/**
* @name GetSuggestionFromUser
* @retval [\b void]
* This method gets suggestion or complaint from user and saves to system.
**/
void GetSuggestionFromUser() {
	SuggestionAndComplaint suggestionAndComplaint;
	ClearConsole();
	PrintToConsole("Lutfen sikayet veya onerinizi yaziniz. Ust menuye donmek icin '0' yazin.");
	string input = GetInput();
	if (input == "0")
		return;
	suggestionAndComplaint.Text = input;
	suggestionAndComplaint.Username = RegisteredUser.kullanici_adi;
	suggestionAndComplaint.Add();
	PrintToConsole("Talebiniz basariyla alindi. Devam etmek icin entera basin.");
	GetInput();
}

/**
* @name FilterProdsByCategory
* @param [in] prods [\b vector]
* @param [in] category [\b string]
* @retval [\b vector]
* This method filters prods by category.
**/
vector<kiyafet> FilterProdsByCategory(vector<kiyafet> prods, string category) {
	vector<kiyafet> returnData;
	for (int i = 0; i < prods.size(); i++)
	{
		if (prods[i].kategori == category)
		{
			returnData.push_back(prods[i]);
		}
	}
	return returnData;
}

/**
* @name FilterProdsBySize
* @param [in] prods [\b vector]
* @param [in] size [\b string]
* @retval [\b vector]
* This method filters prods by size.
**/
vector<kiyafet> FilterProdsBySize(vector<kiyafet> prods, string size) {
	vector<kiyafet> returnData;
	for (int i = 0; i < prods.size(); i++)
	{
		if (prods[i].boyut == size)
		{
			returnData.push_back(prods[i]);
		}
	}
	return returnData;
}

/**
* @name FilterProdsByName
* @param [in] prods [\b vector]
* @param [in] name [\b string]
* @retval [\b vector]
* This method filters prods by name.
**/
vector<kiyafet> FilterProdsByName(vector<kiyafet> prods, string name) {
	vector<kiyafet> returnData;
	for (int i = 0; i < prods.size(); i++)
	{
		if (prods[i].kiyafet_adi == name)
		{
			returnData.push_back(prods[i]);
		}
	}
	return returnData;
}

/**
* @name CreateOrder
* @retval [\b void]
* This method gets selected products from user and prints order if user want.
**/
void CreateOrder() {
	ClearConsole();
	PrintToConsole("Yapacaginiz secimlerdeki ozelliklere sahip urun sepete eklenecektir. Ust menuye donmek icin '0' yazin.");
	Order order;
	bool continueToOrder = true;
	while (continueToOrder)
	{
		vector<kiyafet> products = GetAllProducts();
		string productCategory;
		string productName;
		string productSize;
		string productColor;
		string input;
		while (productCategory == "") {
			PrintToConsole("Lutfen asagidaki kategorilerden birini seciniz.");
			for (int i = 0; i < Categories.size(); i++)
			{
				PrintToConsole(to_string(i + 1) + "-" + Categories[i] + " ", i + 1 == Categories.size());
			}
			input = GetInput();
			if (input == "0")
				return;
			int integerData;

			if (ConvertStrToInt(integerData, input.c_str()))
			{
				if (integerData >= 1 && integerData <= Categories.size())
					productCategory = Categories[integerData - 1];
				else {
					PrintToConsole("Lutfen gecerli bir kategori seciniz.");
				}
			}
			else
				PrintToConsole("Lutfen gecerli bir kategori seciniz.");
		}
		products = FilterProdsByCategory(products, productCategory);

		if (products.size() == 0)
		{
			PrintToConsole("Bu kategoride urun bulunamadi. Menuye donmek icin entera basiniz.");
			GetInput();
			return;
		}
		while (productName == "")
		{
			PrintToConsole("Lutfen asagidaki urunlerden birini seciniz.");
			set<string> grouppedProductNames = GetProductNamesGroupped(products);
			for (int i = 0; i < grouppedProductNames.size(); i++)
			{
				PrintToConsole(to_string(i + 1) + "-" + *next(grouppedProductNames.begin(), i));
			}
			input = GetInput();
			if (input == "0")
				return;
			int integerData;

			if (ConvertStrToInt(integerData, input.c_str()))
			{
				if (integerData >= 1 && integerData <= grouppedProductNames.size())
					productName = *next(grouppedProductNames.begin(), integerData - 1);
				else {
					PrintToConsole("Lutfen gecerli bir urun seciniz.");
				}
			}
			else
				PrintToConsole("Lutfen gecerli bir urun seciniz.");
		}
		products = FilterProdsByName(products, productName);
		while (productSize == "")
		{
			PrintToConsole("Lutfen asagidaki bedenlerden birini seciniz.");
			set<string> grouppedProductSizes = GetProductSizesGroupped(products);
			for (int i = 0; i < grouppedProductSizes.size(); i++)
			{
				PrintToConsole(to_string(i + 1) + "-" + *next(grouppedProductSizes.begin(), i) + " ", i + 1 == grouppedProductSizes.size());
			}
			input = GetInput();
			if (input == "0")
				return;
			int integerData;

			if (ConvertStrToInt(integerData, input.c_str()))
			{
				if (integerData >= 1 && integerData <= grouppedProductSizes.size())
					productSize = *next(grouppedProductSizes.begin(), integerData - 1);
				else {
					PrintToConsole("Lutfen gecerli bir beden seciniz.");
				}
			}
			else
				PrintToConsole("Lutfen gecerli bir beden seciniz.");
		}
		products = FilterProdsBySize(products, productSize);
		while (productColor == "")
		{
			PrintToConsole("Lutfen asagidaki renklerden birini seciniz.");
			set<string> grouppedProductColors = GetProductColoursGroupped(products);
			for (int i = 0; i < grouppedProductColors.size(); i++)
			{
				PrintToConsole(to_string(i + 1) + "-" + *next(grouppedProductColors.begin(), i) + " ", i + 1 == grouppedProductColors.size());
			}
			input = GetInput();
			if (input == "0")
				return;
			int integerData;

			if (ConvertStrToInt(integerData, input.c_str()))
			{
				if (integerData >= 1 && integerData <= grouppedProductColors.size())
					productColor = *next(grouppedProductColors.begin(), integerData - 1);
				else {
					PrintToConsole("Lutfen gecerli bir renk seciniz.");
				}
			}
			else
				PrintToConsole("Lutfen gecerli bir renk seciniz.");
		}
		for (int i = 0; i < products.size(); i++)
		{
			if (products[i].renk != productColor)
			{
				products.erase(products.begin() + i);
				for (int j = i; j < products.size(); j++)
				{
					if (products[i].renk != productColor)
						products.erase(products.begin() + j);
				}
			}
		}
		order.Products.push_back(products[0]);
		order.TotalOrderPrice += products[0].fiyat;
		PrintToConsole("Sepetinize baska urunler eklemek istiyor musunuz? Istiyorsaniz 'E' yaziniz.");
		string data = GetInput();
		transform(data.begin(), data.end(), data.begin(), ::toupper);
		if (data != "E")
			continueToOrder = false;
	}

	PrintToConsole("Sepete eklediginiz urunler asagidaki gibidir. Siparisinizi onayliyor musunuz? Onayliyorsaniz 'E' yaziniz.\n");
	PrintOrderProducts(order);
	string data = GetInput();
	transform(data.begin(), data.end(), data.begin(), ::toupper);
	if (data == "E") {
		if (RegisteredUser.indirim_kodu != "")
		{
			PrintToConsole(to_string(RegisteredUser.DiscountAmount) + " degerinde kuponunuz bulunmaktadir. Kullanmak istiyor musunuz? Istiyorsaniz 'E' yaziniz.\n");
			string data = GetInput();
			transform(data.begin(), data.end(), data.begin(), ::toupper);
			if (data == "E")
			{
				order.TotalOrderPrice -= RegisteredUser.DiscountAmount;
				RegisteredUser.indirim_kodu = "";
				RegisteredUser.DiscountAmount = 0;
				Update(RegisteredUser);
			}
		}
		order.Address = RegisteredUser.adres_ilce;
		order.OrderDate = GetCurrentDesktopTime();
		for (int i = 0; i < order.Products.size(); i++)
			order.ProductGuids.push_back(order.Products[i].guid);
		order.UserGuid = RegisteredUser.guid;
		tuple <kurye, zaman> selectedCourierAndDeliveryTime = SelectOptimalCourier(order.Address);
		order.CourierGuid = get<0>(selectedCourierAndDeliveryTime).guid;
		order.OrderDeliveryDate = get<1>(selectedCourierAndDeliveryTime);
		order.Add();
		PrintToConsole("Siparisiniz basariyla olusturuldu. Siparislerim kismindan durumunu goruntuleyebilirsiniz. Devam etmek icin entera basin.");
		GetInput();
	}
}

/**
* @name CreateProduct
* @retval [\b void]
* This method gets infos from admin and creating new products.
**/
void CreateProduct() {
	kiyafet urun;
	string input;
	ClearConsole();
	PrintToConsole("Lutfen gerekli alanlari doldurunuz. Ust menuye donmek icin '0' girin.");

	while (urun.kategori == "")
	{
		PrintToConsole("Lutfen asagidaki kategorilerden birini seciniz.");
		for (int i = 0; i < Categories.size(); i++)
		{
			PrintToConsole(to_string(i + 1) + "-" + Categories[i] + " ", i + 1 == Categories.size());
		}
		input = GetInput();
		if (input == "0")
			return;
		int integerData;

		if (ConvertStrToInt(integerData, input.c_str()))
		{
			if (integerData >= 1 && integerData <= Categories.size())
				urun.kategori = Categories[integerData - 1];
			else {
				PrintToConsole("Lutfen gecerli bir kategori seciniz.");
			}
		}
		else
			PrintToConsole("Lutfen gecerli bir kategori seciniz.");
	}
	while (urun.boyut == "")
	{
		PrintToConsole("Lutfen asagidaki bedenlerden birini seciniz.");
		for (int i = 0; i < Sizes.size(); i++)
		{
			PrintToConsole(to_string(i + 1) + "-" + Sizes[i] + " ", i + 1 == Sizes.size());
		}
		input = GetInput();
		if (input == "0")
			return;
		int integerData;

		if (ConvertStrToInt(integerData, input.c_str()))
		{
			if (integerData >= 1 && integerData <= Sizes.size())
				urun.boyut = Sizes[integerData - 1];
			else {
				PrintToConsole("Lutfen gecerli bir beden seciniz.");
			}
		}
		else
			PrintToConsole("Lutfen gecerli bir beden seciniz.");
	}
	while (urun.kiyafet_adi == "")
	{
		PrintToConsole("Urun adi: ");
		input = GetInput();
		if (input == "0")
			return;
		if (input.length() >= 4)
			urun.kiyafet_adi = input;
		else
			PrintToConsole("Lutfen gecerli bir urun adi giriniz.");
	}
	while (urun.renk == "")
	{
		PrintToConsole("Renk: ");
		input = GetInput();
		if (input == "0")
			return;
		if (input.length() >= 2)
			urun.renk = input;
		else
			PrintToConsole("Lutfen gecerli bir renk giriniz.");
	}
	while (urun.fiyat == NULL)
	{
		PrintToConsole("Fiyat: ");
		input = GetInput();
		if (input == "0")
			return;
		double price;
		if (ConvertStrToDouble(price, input.c_str()))
			urun.fiyat = price;
		else
			PrintToConsole("Lutfen gecerli bir fiyat giriniz.");
	}

	urun.Add();
	PrintToConsole("Urun basariyla eklendi. Devam etmek icin entera basin.");
	GetInput();
}

/**
* @name CreateCourier
* @retval [\b void]
* This method gets infos from admin and creating new couriers.
**/
void CreateCourier() {
	ClearConsole();
	PrintToConsole("Yeni kurye girisi icin asagidaki alanlari eksiksiz doldurunuz. Ust menuye donmek icin '0' girin.");
	kurye courier;
	string input;
	while (courier.ad_soyad == "") {
		PrintToConsole("Ad ve soyad: ");
		input = GetInput();
		if (input == "0")
			return;
		if (input.length() >= 6)
			courier.ad_soyad = input;
		else
			PrintToConsole("Lutfen gecerli bir ad ve soyad giriniz.");
	}
	while (courier.tel_no == "")
	{
		PrintToConsole("Lutfen basinda 0 ve +90 olmadan telefon numaranizi giriniz.");
		PrintToConsole("Ornek olarak: 5078354525");
		PrintToConsole("Telefon numarasi: ");
		input = GetInput();
		if (input == "0")
			return;
		if (CheckWithRegex("\\(?\\d{3}\\)?-? *\\d{3}-? *-?\\d{4}", input))
			courier.tel_no = input;
		else
			PrintToConsole("Lutfen gecerli bir telefon numarasi giriniz.");
	}
	courier.Add();
	PrintToConsole("Yeni kurye kaydi basariyla yapildi. Devam etmek icin entera basin.");
	GetInput();
}

/**
* @name CreateCoupon
* @retval [\b void]
* This method gets infos from admin and creating new coupons.
**/
void CreateCoupon() {
	ClearConsole();
	PrintToConsole("Kupon olusturmak icin asagidaki alanlari eksiksiz doldurunuz. Ust menuye donmek icin '0' girin.");
	vector<kullanici> customers = GetAllCustomers();
	kullanici selectedCustomer;
	string input;
	while (selectedCustomer.guid == "")
	{
		PrintToConsole("Lutfen asagidaki musterilerden birini seciniz.");
		for (int i = 0; i < customers.size(); i++)
		{
			PrintToConsole(to_string(i + 1) + "-" + customers[i].kullanici_adi + " ", i + 1 == customers.size());
		}
		input = GetInput();
		if (input == "0")
			return;
		int integerData;

		if (ConvertStrToInt(integerData, input.c_str()))
		{
			if (integerData >= 1 && integerData <= customers.size())
				selectedCustomer = customers[integerData - 1];
			else {
				PrintToConsole("Lutfen gecerli bir musteri seciniz.");
			}
		}
		else
			PrintToConsole("Lutfen gecerli bir musteri seciniz.");
	}
	if (selectedCustomer.indirim_kodu != "")
	{
		PrintToConsole("Musterinin kullanilmamis indirimi bulunmaktadir. Bunu iptal edip yeni bir tane tanimlamak istiyor musunuz?\nIstiyorsaniz 'E' yaziniz.");
		input = GetInput();
		if (input == "0")
			return;
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input != "E")
			return;
		selectedCustomer.indirim_kodu = "";
		selectedCustomer.DiscountAmount = 0;
	}
	while (selectedCustomer.indirim_kodu == "")
	{
		PrintToConsole("Indirim kodu: ");
		input = GetInput();
		if (input == "0")
			return;
		if (input.length() >= 4)
			selectedCustomer.indirim_kodu = input;
		else
			PrintToConsole("Indirim kodu 4 karakterden kisa olamaz.");
	}
	while (selectedCustomer.DiscountAmount == 0)
	{
		PrintToConsole("Indirim kodunun degeri: ");
		input = GetInput();
		if (input == "0")
			return;
		double doubleData;

		if (ConvertStrToDouble(doubleData, input.c_str()))
		{
			selectedCustomer.DiscountAmount = doubleData;
		}
		else
			PrintToConsole("Lutfen bir sayi giriniz.");
	}
	Update(selectedCustomer);
	PrintToConsole("Indirim kodu basariyla tanimlandi. Devam etmek icin entera basiniz.");
	GetInput();
}

/**
* @name PrintInvoices
* @retval [\b void]
* This method prints invoices.
**/
void PrintInvoices() {
	ClearConsole();
	Order selectedOrder;
	while (selectedOrder.Id == 0)
	{
		PrintToConsole("Ayrintilarini gormek istediginiz siparisi seciniz. Ust menuye donmek icin '0' giriniz.\n");
		vector<Order> orders = GetAllOrders();
		PrintToConsole("Kullanici", false, 25);
		PrintToConsole("Olusturma Tarihi", false, 20);
		PrintToConsole("Teslim Tarihi", false, 20);
		PrintToConsole("Teslimat Adresi", false, 20);
		PrintToConsole("Toplam Tutar", false, 15);
		PrintToConsole("Durum", true, 20);
		PrintToConsole("------------------------------------------------------------------------------------------------------------------------");
		for (int i = 0; i < orders.size(); i++)
		{
			Order order = orders[i];
			zaman currentTime = GetCurrentDesktopTime();
			PrintToConsole(to_string(i + 1) + "- ", false);
			PrintToConsole(order.User.kullanici_adi, false, 25);
			PrintToConsole(to_string(order.OrderDate.saat) + ":" + to_string(order.OrderDate.dakika), false, 20);
			PrintToConsole(to_string(order.OrderDeliveryDate.saat) + ":" + to_string(order.OrderDeliveryDate.dakika), false, 20);
			PrintToConsole(order.Address, false, 20);
			PrintToConsole(to_string(order.TotalOrderPrice), false, 15);
			if (order.OrderDeliveryDate > currentTime)
				PrintToConsole("Teslim edilecek", true, 15);
			else
				PrintToConsole("Teslim edildi", true, 15);
		}
		string data = GetInput();
		if (data == "0")
			return;
		int integerData;

		if (ConvertStrToInt(integerData, data.c_str()))
		{
			if (integerData >= 1 && integerData <= orders.size())
				selectedOrder = orders[integerData - 1];
			else {
				PrintToConsole("Lutfen gecerli bir siparis seciniz.");
			}
		}
		else
			PrintToConsole("Lutfen gecerli bir siparis seciniz.");
	}

	PrintToConsole("Siparisinizdeki urunler asagidaki gibidir. Ust menuye donmek icin entera basiniz.");
	PrintOrderProducts(selectedOrder);
	GetInput();
}

/**
* @name AdminMenu
* @retval [\b void]
* This method prints admin menu.
**/
void AdminMenu() {
	while (true) {
		ClearConsole();
		PrintToConsole("1- Urun olustur");
		PrintToConsole("2- Yeni kurye girisi");
		PrintToConsole("3- Sikayet ve oneriler");
		PrintToConsole("4- Indirim kodu tanimla");
		PrintToConsole("5- Faturalari goruntule");
		PrintToConsole("0- Geri don");
		string input = GetInput();
		if (input == "1")
		{
			CreateProduct();
		}
		else if (input == "2")
		{
			CreateCourier();
		}
		else if (input == "3")
		{
			ClearConsole();
			PrintToConsole("Ust menuye donmek icin entera basin.");
			vector<SuggestionAndComplaint> suggestions = GetAllSuggestions();
			for (int i = 0; i < suggestions.size(); i++)
			{
				PrintToConsole(to_string(i + 1) + "-" + suggestions[i].Text + " ", i + 1 == suggestions.size());
			}
			GetInput();
		}
		else if (input == "4")
		{
			CreateCoupon();
		}
		else if (input == "5")
		{
			PrintInvoices();
		}
		else if (input == "0")
			return;
		else
			PrintToConsole("Lutfen girdinizi kontrol ediniz.");
	}
}

/**
* @name CustomerMenu
* @retval [\b void]
* This method prints customer menu.
**/
void CustomerMenu() {
	while (true) {
		ClearConsole();
		PrintToConsole("1- Urunleri gor");
		PrintToConsole("2- Siparislerim");
		PrintToConsole("3- Sikayet veya oneride bulun");
		PrintToConsole("4- Sifre degistir");
		PrintToConsole("0- Geri don");
		string input = GetInput();
		if (input == "1")
		{
			CreateOrder();
		}
		else if (input == "2")
		{
			PrintUserOrders();
		}
		else if (input == "3")
		{
			GetSuggestionFromUser();
		}
		else if (input == "4")
		{
			ChangeUserPassword();
		}
		else if (input == "0")
			return;
		else
			PrintToConsole("Lutfen girdinizi kontrol ediniz.");
	}
}

/**
* @name Login
* @param [in] isCustomer [\b bool]
* @retval [\b void]
* This method gets infos from user and allows user to log into the system.
**/
bool Login(bool isCustomer) {
	ClearConsole();
	PrintToConsole("Lutfen cikan bosluklara kullanici bilgilerinizi giriniz. Ust menuye donmek icin '0' girin.");
	string username;
	string password;
	bool isLoggedIn = false;
	while (!isLoggedIn)
	{
		if (isCustomer) {
			PrintToConsole("Kullanici Adi: ", false);
			username = GetInput();
			if (username == "0")
				return false;
			PrintToConsole("Sifre: ", false);
			password = GetInput(true);
			if (password == "0")
				return false;
			isLoggedIn = CheckValidCredentials(username, password, UserRole::customer);
		}
		else {
			PrintToConsole("Sifre: ", false);
			password = GetInput(true);
			if (password == "0")
				return false;
			isLoggedIn = CheckValidCredentials(username, password, UserRole::admin);
		}

		if (!isLoggedIn)
			PrintToConsole("Bu bilgilere ait bir kullanici bulunamadi.");
	}
	PrintToConsole("Basariyla giris yapildi. Devam etmek icin entera basin.");
	GetInput();
	return true;
}

/**
* @name Login
* @retval [\b void]
* This method prints login menu.
**/
void Login() {
	while (true) {
		ClearConsole();
		PrintToConsole("1- Yonetici Girisi");
		PrintToConsole("2- Musteri Girisi");
		PrintToConsole("0- Geri Don");
		string input = GetInput();
		if (input == "1")
		{
			if (Login(false))
				AdminMenu();
		}
		else if (input == "2")
		{
			if (Login(true))
				CustomerMenu();
		}
		else if (input == "0")
			return;
		else
			PrintToConsole("Lutfen girdinizi kontrol ediniz.");
	}

}

/**
* @name Register
* @retval [\b void]
* This methods allows to register new user.
**/
void Register() {
	kullanici yeniKullanici;
	string input;
	ClearConsole();
	PrintToConsole("Lutfen gerekli alanlari doldurunuz. Ust menuye donmek icin '0' girin.");
	while (yeniKullanici.ad_soyad == "")
	{
		PrintToConsole("Ad ve soyad: ");
		input = GetInput();
		if (input == "0")
			return;
		if (input.length() >= 6)
			yeniKullanici.ad_soyad = input;
		else
			PrintToConsole("Lutfen gecerli bir ad ve soyad giriniz.");
	}
	while (yeniKullanici.kullanici_adi == "")
	{
		PrintToConsole("Kullanici adi: ");
		input = GetInput();
		if (input == "0")
			return;
		if (input.length() >= 4)
			if (!IsUsernameUsedBefore(input))
				yeniKullanici.kullanici_adi = input;
			else
				PrintToConsole("Bu kullanici adi kullaniliyor. Lutfen farkli bir kullanici adi seciniz.");
		else
			PrintToConsole("Lutfen gecerli bir kullanici adi giriniz.");

	}
	while (yeniKullanici.eposta == "")
	{
		PrintToConsole("E-Posta: ");
		input = GetInput();
		if (input == "0")
			return;
		if (CheckWithRegex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+", input))
			yeniKullanici.eposta = input;
		else
			PrintToConsole("Lutfen gecerli bir e-posta giriniz.");
	}
	while (yeniKullanici.adres_ilce == "")
	{
		PrintToConsole("Lutfen asagidaki ilcelerden birini seciniz.");
		for (int i = 0; i < Districts.size(); i++)
		{
			PrintToConsole(to_string(i + 1) + "-" + Districts[i] + " ", i + 1 == Districts.size());
		}
		input = GetInput();
		if (input == "0")
			return;
		int integerData;

		if (ConvertStrToInt(integerData, input.c_str()))
		{
			if (integerData >= 1 && integerData <= Districts.size())
				yeniKullanici.adres_ilce = Districts[integerData - 1];
			else {
				PrintToConsole("Lutfen gecerli bir ilce giriniz.");
			}
		}
		else
			PrintToConsole("Lutfen gecerli bir ilce giriniz.");
	}
	while (yeniKullanici.sifre == "")
	{
		PrintToConsole("Sifreniz en az 1 buyuk karakter, en az 1 kucuk karakter, en az 1 ozel karakter, en az 1 adet sayi icermeli, en az 8 karakter uzunlugunda ve en fazla 15 karakter uzunlugunda olmalidir.");
		PrintToConsole("Sifre: ");
		input = GetInput(true);
		if (input == "0")
			return;
		/*
		^ Start anchor
		(?=.*[A-Z].*[A-Z])        Ensure string has two uppercase letters.
		(?=.*[!@#$&*])            Ensure string has one special case letter.
		(?=.*[0-9])               Ensure string has one digits.
		(?=.*[a-z].*[a-z])        Ensure string has two lowercase letters.
		.{8}                      Ensure string is of length 8.
		$                         End anchor.
		*/

		if (CheckWithRegex("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[\\W\\_])[a-zA-Z0-9\\W\\_]{8,15}$", input))
			yeniKullanici.sifre = input;
		else
			PrintToConsole("Lutfen gecerli bir sifre giriniz.");
	}
	while (yeniKullanici.dtarihi == "")
	{
		PrintToConsole("Lutfen gg/aa/yyyy olacak sekilde dogum tarihinizi giriniz.");
		PrintToConsole("Ornek olarak: 25/05/1987");
		PrintToConsole("Dogum tarihi: ");
		input = GetInput();
		if (input == "0")
			return;
		if (CheckWithRegex("^(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\\d\\d$", input))
			yeniKullanici.dtarihi = input;
		else
			PrintToConsole("Lutfen gecerli bir dogum tarihi giriniz.");
	}
	while (yeniKullanici.tel_no == "")
	{
		PrintToConsole("Lutfen basinda 0 ve +90 olmadan telefon numaranizi giriniz.");
		PrintToConsole("Ornek olarak: 5078354525");
		PrintToConsole("Telefon numarasi: ");
		input = GetInput();
		if (input == "0")
			return;
		if (CheckWithRegex("\\(?\\d{3}\\)?-? *\\d{3}-? *-?\\d{4}", input))
			yeniKullanici.tel_no = input;
		else
			PrintToConsole("Lutfen gecerli bir telefon numarasi giriniz.");
	}
	yeniKullanici.Add();

	PrintToConsole("Basariyla kaydoldunuz. Devam etmek icin entera basin.");
	GetInput();
}

/**
* @name MainMenu
* @retval [\b void]
* This method prints main menu.
**/
void MainMenu() {
	while (true) {
		ClearConsole();
		PrintToConsole("1- Sisteme Giris");
		PrintToConsole("2- Sisteme Kayit");
		PrintToConsole("0- Cikis");
		string input = GetInput();
		if (input == "1")
			Login();
		else if (input == "2")
			Register();
		else if (input == "0")
			return;
	}
}

int main()
{
	CreateFiles();
	MainMenu();
}