#pragma once

#include "definition.h"

template <typename T>
class ResourceManager
{
public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager operator=(const ResourceManager&) = delete;
	virtual void loadFromFile(const std::string& name, const std::string& file_path);
	T* get(const std::string& name);
	T* operator[](const std::string& name);
	const T* get(const std::string& name) const;
	~ResourceManager();
protected:
	std::map<std::string, T*> m_resources;
};

template <typename T>
void ResourceManager<T>::loadFromFile(const std::string& name, const std::string& file_path)
{
	assert(m_resources[name] == nullptr); // allready exist
	m_resources[name] = new T();
	if (!m_resources[name]->loadFromFile(file_path))
		throw std::runtime_error(("runtime error can't load resource: " + file_path).c_str());
}

template <>
inline void ResourceManager<sf::Music>::loadFromFile(const std::string& name, const std::string& file_path)
{
	//assert(m_resources[name] == nullptr); // allready exist
	m_resources[name] = new sf::Music();
	if (!m_resources[name]->openFromFile(file_path)) // only music "loadFromFile" function has this name
		throw std::runtime_error(("runtime error can't load resource: " + file_path).c_str());
	m_resources[name]->setLoop(true);
}

template <typename T>
T* ResourceManager<T>::get(const std::string& name)
{
    if (m_resources.find(name) == m_resources.end())
        std::cout << name.c_str() << std::endl;
	assert(m_resources.find(name) != m_resources.end()); //no such resource
	return m_resources[name];
}

template <typename T>
T* ResourceManager<T>::operator[](const std::string& name)
{
	return get(name);
}
 
template <typename T>
const T* ResourceManager<T>::get(const std::string& name) const
{
	assert(m_resources[name] != nullptr); //no such resource
	return m_resources[name];
}

template <typename T>
ResourceManager<T>::~ResourceManager()
{
	return;
	for (auto r : m_resources)
		if (r.second != NULL)
		{
			delete r.second;
			r.second = NULL;
		}
}