#ifndef NODE_H
#define NODE_H

#include <QObject>

template <typename T>
class Node
{
public:
    Node();

	void add(T* obj);

	void remove(T *obj);

	void setParentNode(T *parent){
		m_parent = parent;
	}

    T* parentNode() const {
        return m_parent;
    }

    T* childNode(int i) const {
        return m_childern.at(i);
    }

	const QList<T*> &childNodes() const {
		return m_childern;
	}
protected:

    T *m_parent;
    QList<T*> m_childern;

};

template <typename T>
Node<T>::Node()
{
}

template <typename T>
void Node<T>::add(T *obj)
{
    m_childern.append(obj);
}
template <typename T>
void Node<T>::remove(T *obj)
{
    m_childern.removeOne(obj);
	obj->m_parent = NULL;
}


#endif // NODE_H
