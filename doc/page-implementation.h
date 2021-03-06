/**

\page "Implementation and Usage"

The ordinary implementation an usage of a Facelift interface is described in the Example.
Here we focus on peculiarities of some selected types.

\section Models

QFace models need to be implemented differently compared to basic properties.

In the following we'll consider this QFace definition:
\code
module facelift.imodel 1.0;

interface IModel {
    readonly model<string> theModel;
}
\endcode

We use a model of string types here only to be concise, in real world applications the type is
usually a custom struct.

\note Only "readonly" models are supported by Facelift currently.


\subsection impl-sub1 Implementation

Models can only be implemented in C++, they cannot be implemented in QML. As usual, the
implementation should derive from IModelImplementationBase. Here is the outline of a sample
implementation:

\code
class IModelImplementation : public IModelImplementationBase
{
    Q_OBJECT
public:
    IModelImplementation(QObject *parent = nullptr) : IModelImplementationBase(parent)
    {
        m_theModel.reset(m_items.size(), std::bind(&IModelImplementation::getItem, this, std::placeholders::_1));
    }

    QString getItem(int index)
    {
        return m_items.at(index);
    }

private:
    QStrigList m_items;
};
\endcode

The property adapter will include a public member variable that can be used to provide the model
data. In our case IModelImplementationBase includes \c m_theModel. The \c reset methods of this member
variable should be called (usually in the constructor) with the model size (as int) and a function
that takes an index parameter of type int and returns the corresponding model item. In the example
above the getter is simply called \c getItem.

\subsubsection impl-sub1-sub1 Item Changes
If model items change, this should be notified by emitting the \c dataChanged signal. In our case:
m_theModel.dataChanged(itemIndex) for a single item or m_theModel.dataChanged(first, last), if
several items changed.

\subsubsection impl-sub1-sub2 Item Insertion
If items are inserted into the model, this should be notified by emitting \c beginInsertElements,
followed by endInsertElements. In our case: m_theModel.beginInsertElements(first, last) and
m_theModel.endInsertElements(). The arguments first and last are the indices that the new items
will have after they have been inserted. If only one item is inserted first and last will have the
same index. The actual model update should be done in-between those two method calls.

\subsubsection impl-sub1-sub3 Item Removal
If items are removed from the model, this should be notified by emitting \c beginRemoveElements,
followed by endRemoveElements. In our case: m_theModel.beginRemoveElements(first, last) and
m_theModel.endRemoveElements(). The actual model update should be done in between those two method
calls.

*/
