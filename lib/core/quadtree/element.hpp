
#ifndef _QUADTREE_ELEMENT_HPP

  #define _QUADTREE_ELEMENT_HPP

  template <class class_type>
  class QuadtreeElement {

    public:
      class_type value;

      uint32_t horzPos;
      uint32_t vertPos;
      uint32_t width;
      uint32_t height;

      QuadtreeElement(uint32_t horzPos, uint32_t vertPos, uint32_t width, uint32_t height, class_type val) {
        this->horzPos = horzPos;
        this->vertPos = vertPos;
        this->width = width;
        this->height = height;

        this->value = val;
      }

  };

#endif
