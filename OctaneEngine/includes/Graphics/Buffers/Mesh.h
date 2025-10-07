#pragma once
#include "Vertex.h"

namespace Octane
{
    template <typename Vertex>
    struct Mesh
    {
      OCTANE_INLINE Mesh(const MeshData<Vertex>& data)
      {
        if(data.Vertices.empty())
        {
            OCTANE_ERROR("Mesh()! empty mesh data");
            return;
        }

        //number of vertices and indices
        m_NbrVertex = data.Vertices.size();
        m_NbrIndex = data.Indices.size();

        //generate vertex buffer array
        glGenVertexArrays(1, &m_BufferID);

        //activate/bind vertex array
        glBindVertexArray(m_BufferID);

        //create vertex buffer
        uint32_t VBO = 0u;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, m_NbrVertex * sizeof(Vertex), data.Vertices.data(), GL_STATIC_DRAW);

        //create element buffer
        if(m_NbrIndex != 0u)
        {
            uint32_t EBO = 0u;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ARRAY_BUFFER, EBO);
            glBufferData(GL_ARRAY_BUFFER, m_NbrIndex * sizeof(uint32_t), data.Indices.data(), GL_STATIC_DRAW);
        }

        //handle vertex types
        if(TypeID<Vertex>() == TypeID<ShadedVertex>())
        {
            SetAttribute(0, 3, (void*) offsetof(ShadedVertex, Position));
            SetAtrribute(1, 3, (void*) offsetof(ShadedVertex, Normal));
            SetAttribute(2, 2, (void*) offsetof(ShadedVertex, UVs));
        }
        else if (TypeID<Vertex>() == TypeID<FlatVertex>())
        {
          SetAttribute(0, 4, (void*) offsetof(QuadVertex, Data));
        }
        else
        {
          OCTANE_ERROR(false && "invalid vertex type!");
        }

        //unbid vertex array
        glBindVertexArray(0);

      }  

      OCTANE_INLINE void Draw(uint32_t mode)
      {
        glBindVertexArray(m_BufferID);
        if(m_NbrIndex != 0u)
        {
          glDrawElements(mode, m_NbrIndex, GL_UNSIGNED_INT, 0);
          glBindVertexArray(0);
          return;
        }
        glDrawArrays(mode, 0, m_NbrVertex);
        glBindVertexArray(0);

      }

      OCTANE_INLINE ~Mesh()
      {
        glDeleteVertexArrays(1, &m_BufferID);
      }

      private:
        OCTANE_INLINE void SetAttribute (uint32_t index, int32_t size, const void* value)
        {
          glEnableVertexAttribArray(index);
          glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, sizeOf(Vertex), value);
        }

      private:
        uint32_t m_NbrVertex = 0u;
        uint32_t m_NbrIndex = 0u;
        uint32_t m_BufferID = 0u;

    };

    //3D mesh
    using ShadedMesh = Mesh<ShadedVertex>;
    using Mesh3D = std::shared_ptr<ShadedMesh>;
}