
#ifndef _QUADTREE_ELEMENT_HPP

  #define _QUADTREE_ELEMENT_HPP


  template <class class_type>
  struct QuadtreeElement {
    class_type value;

    uint32_t horzPos;
    uint32_t vertPos;
    uint32_t width;
    uint32_t height;
  };

#endif
