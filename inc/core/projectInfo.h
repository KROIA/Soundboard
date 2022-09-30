#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Author
{
    string firstName;
    string lastName;
    string email;
    string phone;

    string toString() const
    {
        string str = firstName + " " + lastName+"\n";
        if(email.size() > 0)
            str += "E-Mail: "+email+"\n";
        if(phone.size() > 0)
            str += "Phone:  "+phone+"\n";
        return str;
    }
};
struct VersionsInfo
{
    string version;
    string compilationDate;
    string compilationTime;

    string toString() const
    {
        return "Version : V" + version + "\n" +
               "Compiled:  " + compilationDate + " " +compilationTime + "\n";
    }
};

struct ProjectInfo
{
    string projectName;
    string projectYear;
    VersionsInfo versionsInfo;
    vector<Author> authors;

    string toString() const
    {
        string str = "Project: " + projectName + "\n" +
                     "Year   : " + projectYear + "\n" +
                     versionsInfo.toString();
        if(authors.size() > 0)
        {
            str+="Authors:\n";
            for(size_t i=0; i<authors.size(); ++i)
            {
                str += authors[i].toString();
            }
        }
        return str;
    }
};

// defined in main.cpp
extern const ProjectInfo projectInfo;

