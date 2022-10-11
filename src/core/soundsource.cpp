#include "soundsource.h"
#include <QFile>

SoundSource::SoundSource()
{

}
SoundSource::SoundSource(const std::string &absolutePath)
{
    setAbsolutePath(absolutePath);
}
SoundSource::SoundSource(const std::string &root, const std::string &relativePath)
{
    m_rootPath = root;
    m_relativePath = relativePath;
}
SoundSource::~SoundSource()
{

}

void SoundSource::setAbsolutePath(const std::string absolutePath)
{
    std::string::size_type lastSlash = absolutePath.find_last_of("\\");
    if(lastSlash == std::string::npos)
    {
        m_relativePath = absolutePath;
    }
    else
    {
        m_rootPath = absolutePath.substr(0,lastSlash);
        m_relativePath = absolutePath.substr(lastSlash+1);
    }
}
void SoundSource::setRootPath(const std::string &path)
{
    m_rootPath = path;
}
void SoundSource::setRelativePath(const std::string &path)
{
    m_relativePath = path;
}

bool SoundSource::isValid()
{
    return QFile::exists(getAbsolutePath().c_str());
}
const std::string &SoundSource::getRootPath() const
{
    return m_rootPath;
}
const std::string &SoundSource::getRelativePath() const
{
    return m_relativePath;
}
std::string SoundSource::getAbsolutePath() const
{
    if(m_rootPath.size() == 0)
        return m_relativePath;
    return m_rootPath+"\\"+m_relativePath;
}
/*void SoundSource::save(QXmlStreamWriter *writer)
{
    if(!writer) return;
    writer->writeStartElement("SoundSource");
    writer->writeTextElement("rootPath",m_rootPath.c_str());
    writer->writeTextElement("relativePath",m_relativePath.c_str());
   // writer->writeAttribute("rootPath",m_rootPath.c_str());
   // writer->writeAttribute("relativePath",m_relativePath.c_str());
    writer->writeEndElement();
}
void SoundSource::load(QXmlStreamReader *reader)
{
    if(!reader) return;
    qDebug() << reader->readNext();
}
*/
