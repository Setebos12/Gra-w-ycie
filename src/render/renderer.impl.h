// Filename: renderer.impl.h
//
// Implementation of draw that is template
//
// Author: Piotr Pyrak

namespace MVC {
template <typename T>
void Renderer::draw(const std::vector<std::shared_ptr<T>>& all_objects)
    requires std::is_base_of_v<Render::IRenderObject, T>
{
  for (const auto &obj : all_objects) {
    obj->draw(*drawer_);
  }

  drawer_->refresh();
}
} // namespace MVC
