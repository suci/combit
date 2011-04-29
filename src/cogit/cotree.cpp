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
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "cotree.h" 

CoTree::CoTree(CoRepo *repo, QString id, qint32 mode, QString name):CoObject(repo,id,CoObject::Tree)
{
	m_name = name;
	m_mode = mode;
	QStringList cmd;
	cmd << "ls-tree" << id;
	QString out;
	bool success = repo->repoGit()->execute(cmd, CoKwargs(), &out);
	if(success)
	{
		QString str;
		foreach(str, out.split(QRegExp("\\n")));
		{
			str = str.trimmed();
			CoObject * obj = CoObject::getObjectFromString(repo, str);
			m_contents.insert(obj->name(),obj);
		}
	}
}

CoTree::~CoTree()
{
}

const qint32 CoTree::mode() const
{
	return m_mode;
}

const QString CoTree::name() const
{
	return m_name;
}


const QString CoTree::baseName() const
{
	QString base;
	QFileInfo fi(m_name);
	base = fi.baseName();
	return base;
}

int CoTree::count() const
{
	return m_contents.size();
}

bool CoTree::contains(QString &name) const
{
	return m_contents.contains(name);
}

const CoObject* CoTree::item(QString &name) const
{
	return m_contents.value(name);
}

QList<CoObject*> CoTree::items() const
{
	return m_contents.values();
}

QStringList CoTree::itemNames() const
{
	return m_contents.keys();
}

static QHash<QString, CoObject*> getContentsFromId(const CoRepo* repo, QString id)
{
	QStringList cmd;
	cmd << "ls-tree" << id;
	QString out;
	bool success = repo->repoGit()->execute(cmd, CoKwargs(), &out);
	if(success)
	{
		QString str;
		foreach(str, out.split(QRegExp("\\n")));
		{
			str = str.trimmed();
			CoObject * obj = CoObject::getObjectFromString(repo, str);
			m_contents.insert(obj->name(),obj);
		}
	}
}
