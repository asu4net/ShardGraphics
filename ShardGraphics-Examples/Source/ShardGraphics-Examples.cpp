#include <ShardGraphics.h>

using namespace Shard::Graphics;
using namespace Shard;

// implementar precompiled headers

int main()
{
    const std::shared_ptr<Window> window(Window::Create());
    window->Initialize();
    
    Renderer2D& renderer2D = Renderer2D::CreateSingleton();
    renderer2D.Initialize();
    
    ImGuiRenderer& imGuiRenderer = ImGuiRenderer::CreateSingleton();
    imGuiRenderer.Initialize(window);
    
    imGuiRenderer.CreateRootWidget("Test Widget")->UpdateEvent().Add([]()
    {
       ImGui::Button("My button"); 
    });

    /////////////////////////
    /// TEST TRIANGLE
    ////////////////////////

    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::unique_ptr<Shader> shader;
    
    vertexArray.reset(VertexArray::Create());

    constexpr float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };
        
    vertexBuffer.reset(VertexBuffer::Create(vertices, static_cast<uint32_t>(sizeof(vertices))));
    
    const BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" }
    };

    vertexBuffer->SetLayout(layout);

    vertexArray->AddVertexBuffer(vertexBuffer);

    constexpr  uint32_t indices[3] = { 0, 1, 2 };
    indexBuffer.reset(IndexBuffer::Create(indices, static_cast<uint32_t>(sizeof(indices) / sizeof(uint32_t))));
    vertexArray->AddIndexBuffer(indexBuffer);

    const std::string vertexSource = R"(
             #version 410 core
             
             layout(location = 0) in vec3 a_Position;
             layout(location = 1) in vec4 a_Color;

             out vec4 v_Color;

             void main()
             {
                 gl_Position = vec4(a_Position + vec3(0.2, 0.0, 0.0), 1.0);
                 v_Color = a_Color;
             }
         )";

    const std::string fragmentSource = R"(
             #version 410 core
             
             layout(location = 0) out vec4 color;
             in vec4 v_Color;
             
             void main()
             {
                 color = v_Color;
             }
         )";
         
    shader.reset(Shader::Create(vertexSource, fragmentSource));
    
    while (window->KeepOpened())
    {
        renderer2D.ClearColor(window->GetBackgroundColor());
        shader->Bind();
        vertexArray->Bind();
        renderer2D.DrawIndices(indexBuffer->GetCount());
        imGuiRenderer.Update();
        window->Update();
    }

    imGuiRenderer.Finalize();
    ImGuiRenderer::DestroySingleton();
    Renderer2D::DestroySingleton();
    window->Finalize();
}