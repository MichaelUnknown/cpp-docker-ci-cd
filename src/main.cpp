#include <iostream>
#include <string>
#include <unordered_map>

#include "crow.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/hello")
    ([](const crow::request& req) {
        // check params
        std::cout << "Params: " << req.url_params << "\n";
        std::cout << "The key 'language' was " << (req.url_params.get("language") == nullptr ? "not " : "") << "found.\n";

        if (req.url_params.get("language") == nullptr)
        {
            // return bad request
            return crow::response(400);
        }
        const auto language = req.url_params.get("language");

        // see if langauge was found
        const std::unordered_map<std::string, std::string> answers{
            {"en", "Hello from the "},
            {"de", "Hallo von der "},
        };
        const auto answer = answers.find(language);
        if (answer == answers.end())
        {
            std::cout << "Greeting for lanuage '" << language << "' is not available\n";
            return crow::response(400, "Greeting for lanuage '" + std::string(language) + "' is not available\n");
        }

        crow::json::wvalue ret({{"answer", answer->second + "WebAPI"}});
        return crow::response(200, ret);
    });

    app.port(3080).multithreaded().run();
}
