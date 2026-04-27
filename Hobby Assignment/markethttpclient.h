#pragma once
#include "HttpClient.h"
#include <string>

using namespace std;

class MarketHTTPClient : public HttpClient
{
    string dataResponse;

    protected:
        void StartOfData() override
        {
            dataResponse.clear();
        }

        void Data(const char* data, const unsigned int size) override
        {
            dataResponse.append(data, size);
        }

        void EndOfData() override
        {
            cout << dataResponse << endl;
        }

    public:
        const string& GetResponse() const {
            return dataResponse;
        }
};