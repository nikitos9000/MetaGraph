#include "GStorage.h"

GStorageVertexSet::GStorageVertexSet(const VertexSet& vertex_set, const string& name) :
                                     _name(name), _vertex_set(vertex_set)
{
}

GStorageVertexSet::GStorageVertexSet(const GStorageVertexSet& other) :
                                     _name(other._name), _vertex_set(other._vertex_set)
{
}

VertexSet& GStorageVertexSet::getVertexSet()
{
    return _vertex_set;
}

const VertexSet& GStorageVertexSet::getVertexSet() const
{
    return _vertex_set;
}

void GStorageVertexSet::setName(const string& name)
{
    _name = name;
}

const string& GStorageVertexSet::getName() const
{
    return _name;
}

GStorageArcSet::GStorageArcSet(const ArcSet& arc_set, const string& name) :
                               _name(name), _arc_set(arc_set)
{
}

GStorageArcSet::GStorageArcSet(const GStorageArcSet& other) :
                               _name(other._name), _arc_set(other._arc_set)
{
}

ArcSet& GStorageArcSet::getArcSet()
{
    return _arc_set;
}

const ArcSet& GStorageArcSet::getArcSet() const
{
    return _arc_set;
}

void GStorageArcSet::setName(const string& name)
{
    _name = name;
}

const string& GStorageArcSet::getName() const
{
    return _name;
}

GStoragePath::GStoragePath(const Path& path, const string& name) :
                           _name(name), _path(path)
{
}

GStoragePath::GStoragePath(const GStoragePath& other) :
                           _name(other._name), _path(other._path)
{
}

Path& GStoragePath::getPath()
{
    return _path;
}

const Path& GStoragePath::getPath() const
{
    return _path;
}

void GStoragePath::setName(const string& name)
{
    _name = name;
}

const string& GStoragePath::getName() const
{
    return _name;
}

GStorageDiGraph::GStorageDiGraph(const DiGraph& digraph, const string& name) :
                                 _name(name), _digraph(digraph)
{
}

GStorageDiGraph::GStorageDiGraph(const GStorageDiGraph& gstorage_digraph) :
                                 _digraph(gstorage_digraph._digraph),
                                 _vertex_set_list(gstorage_digraph._vertex_set_list),
                                 _arc_set_list(gstorage_digraph._arc_set_list),
                                 _path_list(gstorage_digraph._path_list)
{
}

size_t GStorageDiGraph::_newVertexSetId() const
{
    map<size_t, GStorageVertexSet>::const_iterator iterator = _vertex_set_list.begin();
    map<size_t, GStorageVertexSet>::const_iterator end_iterator = _vertex_set_list.end();

    size_t new_id = 1;

    for (; iterator != end_iterator; ++iterator, ++new_id)
    {
        size_t id = (*iterator).first;
        if (new_id != id) break;
    }
    return new_id;
}

size_t GStorageDiGraph::_newArcSetId() const
{
    map<size_t, GStorageArcSet>::const_iterator iterator = _arc_set_list.begin();
    map<size_t, GStorageArcSet>::const_iterator end_iterator = _arc_set_list.end();

    size_t new_id = 1;

    for (; iterator != end_iterator; ++iterator, ++new_id)
    {
        size_t id = (*iterator).first;
        if (new_id != id) break;
    }
    return new_id;
}

size_t GStorageDiGraph::_newPathId() const
{
    map<size_t, GStoragePath>::const_iterator iterator = _path_list.begin();
    map<size_t, GStoragePath>::const_iterator end_iterator = _path_list.end();

    size_t new_id = 1;

    for (; iterator != end_iterator; ++iterator, ++new_id)
    {
        size_t id = (*iterator).first;
        if (new_id != id) break;
    }
    return new_id;
}

DiGraph& GStorageDiGraph::getDiGraph()
{
    return _digraph;
}

const DiGraph& GStorageDiGraph::getDiGraph() const
{
    return _digraph;
}

void GStorageDiGraph::setName(const string &name)
{
    _name = name;
}

const string& GStorageDiGraph::getName() const
{
    return _name;
}

size_t GStorageDiGraph::addVertexSet(const GStorageVertexSet& vertex_set)
{
    size_t id = _newVertexSetId();

    bool inserted = _vertex_set_list.insert(map<size_t, GStorageVertexSet>::value_type(id, vertex_set)).second;

    if (!inserted)
    {
        throw logic_error("GStorageDiGraph::addVertexSet() fail.");
    }
    return id;
}

size_t GStorageDiGraph::addArcSet(const GStorageArcSet& arc_set)
{
    size_t id = _newArcSetId();

    bool inserted = _arc_set_list.insert(map<size_t, GStorageArcSet>::value_type(id, arc_set)).second;

    if (!inserted)
    {
        throw logic_error("GStorageDiGraph::addArcSet() fail.");
    }
    return id;
}

size_t GStorageDiGraph::addPath(const GStoragePath& path)
{
    size_t id = _newPathId();

    bool inserted = _path_list.insert(map<size_t, GStoragePath>::value_type(id, path)).second;

    if (!inserted)
    {
        throw logic_error("GStorageDiGraph::addPath() fail.");
    }
    return id;
}


bool GStorageDiGraph::hasVertexSet(size_t id) const
{
    return _vertex_set_list.find(id) != _vertex_set_list.end();
}

bool GStorageDiGraph::hasArcSet(size_t id) const
{
    return _arc_set_list.find(id) != _arc_set_list.end();
}

bool GStorageDiGraph::hasPath(size_t id) const
{
    return _path_list.find(id) != _path_list.end();
}

GStorageVertexSet& GStorageDiGraph::getVertexSet(size_t id)
{
    map<size_t, GStorageVertexSet>::iterator iterator = _vertex_set_list.find(id);
    map<size_t, GStorageVertexSet>::iterator end_iterator = _vertex_set_list.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("GStorageDiGraph::getVertexSet() fail.");
    }
    return iterator->second;
}

const GStorageVertexSet& GStorageDiGraph::getVertexSet(size_t id) const
{
    map<size_t, GStorageVertexSet>::const_iterator iterator = _vertex_set_list.find(id);
    map<size_t, GStorageVertexSet>::const_iterator end_iterator = _vertex_set_list.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("GStorageDiGraph::getVertexSet() fail.");
    }
    return iterator->second;
}

GStorageArcSet& GStorageDiGraph::getArcSet(size_t id)
{
    map<size_t, GStorageArcSet>::iterator iterator = _arc_set_list.find(id);
    map<size_t, GStorageArcSet>::iterator end_iterator = _arc_set_list.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("GStorageDiGraph::getArcSet() fail.");
    }
    return iterator->second;
}

const GStorageArcSet& GStorageDiGraph::getArcSet(size_t id) const
{
    map<size_t, GStorageArcSet>::const_iterator iterator = _arc_set_list.find(id);
    map<size_t, GStorageArcSet>::const_iterator end_iterator = _arc_set_list.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("GStorageDiGraph::getArcSet() fail.");
    }
    return iterator->second;
}

GStoragePath& GStorageDiGraph::getPath(size_t id)
{
    map<size_t, GStoragePath>::iterator iterator = _path_list.find(id);
    map<size_t, GStoragePath>::iterator end_iterator = _path_list.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("GStorageDiGraph::getPath() fail.");
    }

    return iterator->second;
}

const GStoragePath& GStorageDiGraph::getPath(size_t id) const
{
    map<size_t, GStoragePath>::const_iterator iterator = _path_list.find(id);
    map<size_t, GStoragePath>::const_iterator end_iterator = _path_list.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("GStorageDiGraph::getPath() fail.");
    }

    return (*iterator).second;
}

void GStorageDiGraph::removeVertexSet(size_t id)
{
    if (_vertex_set_list.erase(id) == 0)
    {
        throw invalid_argument("GStorageDiGraph::removeVertexSet() fail.");
    }
}

void GStorageDiGraph::removeArcSet(size_t id)
{
    if (_arc_set_list.erase(id) == 0)
    {
        throw invalid_argument("GStorageDiGraph::removeArcSet() fail.");
    }
}

void GStorageDiGraph::removePath(size_t id)
{
    if (_path_list.erase(id) == 0)
    {
        throw invalid_argument("GStorageDiGraph::removePath() fail.");
    }
}

GStorageDiGraph::VertexSetIterator GStorageDiGraph::beginVertexSetIterator() const
{
    return _vertex_set_list.begin();
}

GStorageDiGraph::VertexSetIterator GStorageDiGraph::endVertexSetIterator() const
{
    return _vertex_set_list.end();
}

GStorageDiGraph::ArcSetIterator GStorageDiGraph::beginArcSetIterator() const
{
    return _arc_set_list.begin();
}

GStorageDiGraph::ArcSetIterator GStorageDiGraph::endArcSetIterator() const
{
    return _arc_set_list.end();
}

GStorageDiGraph::PathIterator GStorageDiGraph::beginPathIterator() const
{
    return _path_list.begin();
}

GStorageDiGraph::PathIterator GStorageDiGraph::endPathIterator() const
{
    return _path_list.end();
}

GStorage::GStorage() : _gstorage_digraph_list()
{
}

GStorage::GStorage(const GStorage& gstorage) : _gstorage_digraph_list(gstorage._gstorage_digraph_list)
{
}

GStorage::~GStorage()
{
}

size_t GStorage::_newDiGraphId() const
{
    map<size_t, GStorageDiGraph>::const_iterator iterator = _gstorage_digraph_list.begin();
    map<size_t, GStorageDiGraph>::const_iterator end_iterator = _gstorage_digraph_list.end();

    size_t new_id = 1;

    for (; iterator != end_iterator; ++iterator, ++new_id)
    {
        size_t id = iterator->first;
        if (new_id != id) break;
    }
    return new_id;
}

size_t GStorage::addDiGraph(const GStorageDiGraph& digraph)
{
    size_t id = _newDiGraphId();

    map<size_t, GStorageDiGraph>::value_type insert_value(id, digraph);

    bool inserted = _gstorage_digraph_list.insert(insert_value).second;

    if (!inserted)
    {
        throw logic_error("GStorage::addGStorageDiGraph() fail.");
    }
    return id;
}

bool GStorage::hasDiGraph(size_t id) const
{
    return _gstorage_digraph_list.find(id) != _gstorage_digraph_list.end();
}

GStorageDiGraph& GStorage::getDiGraph(size_t id)
{
    map<size_t, GStorageDiGraph>::iterator iterator = _gstorage_digraph_list.find(id);
    map<size_t, GStorageDiGraph>::iterator end_iterator = _gstorage_digraph_list.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("GStorage::getGStorageDiGraph() fail.");
    }
    return (*iterator).second;
}

const GStorageDiGraph& GStorage::getDiGraph(size_t id) const
{
    map<size_t, GStorageDiGraph>::const_iterator iterator = _gstorage_digraph_list.find(id);
    map<size_t, GStorageDiGraph>::const_iterator end_iterator = _gstorage_digraph_list.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("GStorage::getGStorageDiGraph() fail.");
    }
    return (*iterator).second;
}

void GStorage::removeDiGraph(size_t id)
{
    if (_gstorage_digraph_list.erase(id) == 0)
    {
        throw invalid_argument("GStorage::removeDiGraph() fail.");
    }
}

GStorage::DiGraphIterator GStorage::beginDiGraphIterator() const
{
    return _gstorage_digraph_list.begin();
}

GStorage::DiGraphIterator GStorage::endDiGraphIterator() const
{
    return _gstorage_digraph_list.end();
}
