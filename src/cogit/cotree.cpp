/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cotree.cpp
 *	\brief CoTree类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "cotree.h" 
#include "corepo.h"
#include "coblob.h"

#include <QStringList>
#include <QRegExp>

CoTree::CoTree():CoObject(NULL, "", CoObject::Tree)
{
	m_name = "";
	m_mode = 0;
	m_isInited = false;
	m_contents = QHash<QString, CoObject*>();
}

CoTree::CoTree(CoRepo *repo, QString id, qint32 mode, QString name):CoObject(repo,id,CoObject::Tree)
{
	m_name = name;
	m_mode = mode;
	m_isInited = false;
	m_contents = QHash<QString,CoObject*>();
}

CoTree::~CoTree()
{
}

bool CoTree::isValid() const
{
	return CoObject::isValid() && m_mode != 0 && !m_name.isEmpty();
}

qint32 CoTree::mode() const
{
	return m_mode;
}

QString CoTree::name() const
{
	return m_name;
}

int CoTree::count()
{
	if(!m_isInited)
		initContents();
	return m_contents.size();
}

bool CoTree::contains(QString &name)
{
	if(!m_isInited)
		initContents();
	return m_contents.contains(name);
}

CoObject* CoTree::item(QString &name)
{
	if(!m_isInited)
		initContents();
	return m_contents.value(name);
}

QList<CoObject*> CoTree::items()
{
	if(!m_isInited)
		initContents();
	return m_contents.values();
}

QStringList CoTree::itemNames()
{
	if(!m_isInited)
		initContents();
	return m_contents.keys();
}

QHash<QString, CoObject*> CoTree::getContentsFromId(CoRepo* repo, QString id)
{
	if(repo == NULL || id.isEmpty())
		return QHash<QString,CoObject*>();
	QHash<QString, CoObject*> contents;
	QStringList cmd;
	cmd << "ls-tree" << id;
	QString out,error;
	bool success = repo->repoGit()->execute(cmd, CoKwargs(), &out, &error);
	if(success)
	{
		QString str;
		foreach(str, out.trimmed().split("\n"))
		{
			str = str.trimmed();
			CoObject * obj = CoObject::objectFromString(repo, str);
			switch(obj->type())
			{
				case CoObject::Blob:
					contents.insert(static_cast<CoBlob*>(obj)->name(),obj);
					break;
				case CoObject::Tree:
					contents.insert(static_cast<CoTree*>(obj)->name(),obj);
					break;
				default:
					break;
			}
		}
	}
	else
	{
	}
	return contents;
}

void CoTree::initContents()
{
	if(!isValid())
		return;
	QStringList cmd;
	cmd << "ls-tree" << id();
	QString out, error;
	bool success = repo()->repoGit()->execute(cmd, CoKwargs(), &out, &error);
	if(success)
	{
		QString str;
		foreach(str, out.trimmed().split("\n"))
		{
			str = str.trimmed();
			CoObject * obj = CoObject::objectFromString(repo(), str);
			switch(obj->type())
			{
				case CoObject::Blob:
					m_contents.insert(static_cast<CoBlob*>(obj)->name(),obj);
					break;
				case CoObject::Tree:
					m_contents.insert(static_cast<CoTree*>(obj)->name(),obj);
					break;
				default:
					break;
			}
			m_isInited = true;
		}
	}
	else
	{
	}
}
