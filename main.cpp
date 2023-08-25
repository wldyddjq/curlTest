#include <stdio.h>
#include <string>
#include <iostream>
#include "jsoncpp/json/json.h"

#include "curl.h"

int main(int _argc, char *_argv[]) {
    CURL_Handler	curl_handle;//핸들러
    
    curl_handle.set_debug_print(); //디버그출력 on
    curl_handle.init(); //is_init = true
		
    curl_handle.set_header_content("Content-Type", 	"application/json"); //header set [Content-Type : application/json]
    
    // POST 사용 시 string data를 인자로 사용
    //std::string data = "{\"id\" : 1}";
    //curl_handle.set_post(data);

    curl_handle.set_server_info("https://jsonplaceholder.typicode.com/users"); //https://httpbin.org/get
    curl_handle.request();
    
    string response = curl_handle.response();  //responst : json

    //////////json parsing///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Json::Reader reader ;
    Json::Value root;

    bool retval = reader.parse(response, root);
    if(!retval)
    {
        std::cout<<"Failed to Parse Json : "<<reader.getFormattedErrorMessages();
        return 0;
    }
    
    
    int len = root.size();
    for(int i = 0 ; i < len ; i++ )
    {
        // std::cout<<"[ id"<<i + 1<<" ]"<<std::endl<<std::endl;
        // std::cout<<root[i]<<std::endl;

        if(root[i]["id"] == 7)
            std::cout<<root[i]["name"]<<std::endl;

    }
    // Json::Value ids = root["id : 1"]; 
    // std::cout<<ids<<endl;
    // for(int i = 0 ; i < (int)ids.size(); i++)
    // {
    //     std::cout<<ids[i]<<std::endl;
    // }
    // Json::ValueIterator it = ids.begin();
    // std::cout<<*it<<std::endl;
    // for(auto it = id.begin() ; it != id.end() ; it ++)
    // {
    //     std::cout<<(*it)["username"]<<" : "<<(*it)["phone"]<<std::endl;
    // }



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //printf("response : [%s]\n", response.c_str());
    
    curl_handle.clear();

    return 0;
}