#pragma once

#include <string>
#include <vector>

struct Author
{
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;

    std::string toString() const
    {
        std::string str = firstName + " " + lastName + "\n";
        if(email.size() > 0)
            str += "E-Mail: "+email+"\n";
        if(phone.size() > 0)
            str += "Phone:  "+phone+"\n";
        return str;
    }
};
struct VersionsInfo
{
    std::string version;
    std::string compilationDate;
    std::string compilationTime;

    std::string toString() const
    {
        return "Version : V" + version + "\n" +
               "Compiled:  " + compilationDate + " " +compilationTime + "\n";
    }
};

struct ProjectInfo
{
    std::string projectName;
    std::string projectYear;
    VersionsInfo versionsInfo;
    std::vector<Author> authors;

    std::string toString() const
    {
        std::string str = "Project: " + projectName + "\n" + "Year   : " + projectYear + "\n"
                          + versionsInfo.toString();
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

