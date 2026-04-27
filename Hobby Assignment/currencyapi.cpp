#include "currencyapi.h"
#include "markethttpclient.h"
#include "json.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;
using json = nlohmann::json;

// Struct for holding the currency data
struct Currency
{
    string code;
    string name;
    string symbol;
    double rate_usd = 1.0;
};

void runCurrencyAPI()
{
    {
        MarketHTTPClient client;

        if (!client.Connect("api.macomb.io")){
            cerr << "Failed to connect to the API." << endl;
            return;
        }

        bool ok = client.Get("/currency", { { "limit", "20"}}); // Get top 20 currencies

        if (!ok){
            cerr << "Failed to get currency data." << endl;
            return;
        }

        const string& body = client.GetResponse();

        vector<Currency> currencies;

        try{

            json j = json::parse(body);

            for (const auto& item : j["currencies"]){
                Currency c;
                c.code = item["code"].get<string>();
                c.name = item["name"].get<string>();
                c.symbol = item["symbol"].get<string>();
                c.rate_usd = item["rate_usd"].get<double>();

                currencies.push_back(c);
            }
        } catch(const json::exception& e){
            cerr << "JSON parsing error: " << e.what() << endl;
            return;
        }

        // Display the Data
        cout << "[Get] Loaded " << currencies.size() << " currencies:\n" << endl;

        cout << fixed << setprecision(4);

        cout << left << setw(6) << "Code" << setw(22) << "Name" << setw(8) << "Symbol" << "Rate (USD)" << endl;
        cout << string(60, '-') << endl; // Dash Line

        for (const auto& c : currencies){
            cout << left << setw(6) << c.code << setw(22) << c.name << setw(8) << c.symbol << c.rate_usd << endl;
        }
    }

    {
        MarketHTTPClient client;

        if(!client.Connect("api.macomb.io"))
        {
            cerr << "Failed to connect to the API." << endl;
            return;
        }

        bool ok = client.Get("/currency",
        {
            { "from", "USD"},
            {"to", "EUR"},
            {"amount", "1000"}
        });

        if (!ok){
            cerr << "Failed to get conversion data." << endl;
            return;
        }

        try {
            json j = json::parse(client.GetResponse());

            const json& conv = j["conversion"];

            cout << fixed << setprecision(2);

            cout << "\n[Get] Currency Conversion:\n" << endl;
            cout << "  " << conv.value("from_symbol","$")
                 << conv.value("amount", 0.0) << " "
                 << conv.value("from", "USD") << "  =>  "
                 << conv.value("to_symbol", "")
                 << conv.value("result", 0.0) << " "
                 << conv.value("to", "EUR") << endl;
            cout << "  Rate: 1 " << conv.value("from","USD")
                 << " = " << setprecision(6) << conv.value("rate", 1.0)
                 << " " << conv.value("to","EUR") << endl; 
        } catch (const json::exception& e){
            cerr << "JSON parsing error: " << e.what() << endl;
            return;
        }
    }

    {
        json payload;
        payload["code"] = "MKC";
        payload["name"] = "MarketPlace Credits";
        payload["symbol"] = "MC";
        payload["rate_usd"] = 4.20;

        string bodyStr = payload.dump(); // Converting JSON to string

        MarketHTTPClient client;

        if(!client.Connect("api.macomb.io"))
        {
            cerr << "Failed to connect to the API." << endl;
            return;
        }

        bool ok = client.Post("/currency", bodyStr);

        if (!ok){
            cerr << "Failed to post new currency." << endl;
            return;
        }


        try {
            json j = json::parse(client.GetResponse());

            cout << "\n[Post] Created Currency:\n" << endl;
            cout << "  Code: " << j.value("code", "") << endl;
            cout << "  Name: " << j.value("name", "") << endl;
            cout << "  Symbol: " << j.value("symbol", "") << endl;
            cout << "  Rate (USD): " << j.value("rate_usd", 0.0) << endl;
        } catch (const json::exception& e){
            cerr << "JSON parsing error: " << e.what() << endl;
            return;
        }
    }

}
