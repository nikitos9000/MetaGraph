#include "DiGraphWeighted.h"

DiGraphWeighted::DiGraphWeighted() :
        DiGraph(),
        m_arc_weight_info_array(0)
{}

DiGraphWeighted::DiGraphWeighted(size_t vertex_count) :
        DiGraph(vertex_count),
        m_arc_weight_info_array(vertex_count)
{}

DiGraphWeighted::DiGraphWeighted(const DiGraphWeighted& other) :
        DiGraph(other),
        m_arc_weight_info_array(other.m_arc_weight_info_array)
{}

DiGraphWeighted::~DiGraphWeighted()
{

}
