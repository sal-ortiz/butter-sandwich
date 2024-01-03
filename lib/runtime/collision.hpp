
#ifndef _COLLISION_HPP

  #define _COLLISION_HPP


  //struct CollisionDataEntry {
  //  char* identifier;
  //
  //  uint32_t horzPos;
  //  uint32_t vertPos;
  //  uint32_t width;
  //  uint32_t height;
  //
  //  void*(*callback)(void*, void*, void*);
  //};



  //List<CollisionDataEntry*>* _collisionDataStore = new List<CollisionDataEntry*>();


  class Collision {

    public:

      static bool evaluate(Position* basePos, Size* baseSize, Position* testPos, Size* testSize) {

        if (
          (
            (
              (basePos->horz > testPos->horz) && (basePos->horz < testPos->horz + testSize->horz) &&
              (basePos->vert > testPos->vert) && (basePos->vert < testPos->vert + testSize->vert)
            ) || (
              (basePos->horz + baseSize->horz > testPos->horz) && (basePos->horz + baseSize->horz < testPos->horz + testSize->horz) &&
              (basePos->vert + baseSize->vert > testPos->vert) && (basePos->vert + baseSize->vert < testPos->vert + testSize->vert)
            )
          ) || (
            (
              (testPos->horz > basePos->horz) && (testPos->horz < basePos->horz + baseSize->horz) &&
              (testPos->vert > basePos->vert) && (testPos->vert < basePos->vert + baseSize->vert)
            ) || (
              (testPos->horz + testSize->horz > basePos->horz) && (testPos->horz + testSize->horz < basePos->horz + baseSize->horz) &&
              (testPos->vert + testSize->vert > basePos->vert) && (testPos->vert + testSize->vert < basePos->vert + baseSize->vert)
            )
          )
        ) {
          return true;
        }

        return false;
      }

      //static void insert(uint32_t elHorzPos, uint32_t elVertPos, uint32_t elWidth, uint32_t elHeight, void*(*elCallback)(void*, void*, void*)) {
      //  CollisionDataEntry* newEntry = new CollisionDataEntry();
      //
      //  newEntry->horzPos = elHorzPos;
      //  newEntry->vertPos = elVertPos;
      //  newEntry->width = elWidth;
      //  newEntry->height = elHeight;
      //  newEntry->callback = elCallback;
      //
      //  _collisionDataStore->push(newEntry);
      //}

      //static void clear() {
      //  uint32_t numElements = _collisionDataStore->getLength();
      //
      //  for (uint32_t elIdx = 0; elIdx < numElements; elIdx++) {
      //    CollisionDataEntry* element = _collisionDataStore->get(elIdx);
      //
      //    delete element;
      //  }
      //
      //  delete _collisionDataStore;
      //
      //  _collisionDataStore = new List<CollisionDataEntry*>();
      //}

      //static void evaluate() {
      //  List<CollisionDataEntry*>* retList = new List<CollisionDataEntry*>();
      //
      //  uint32_t numElements = _collisionDataStore->getLength();
      //
      //  for (uint32_t baseElIdx = 0; baseElIdx < numElements; baseElIdx++) {
      //    CollisionDataEntry* baseEl = _collisionDataStore->get(baseElIdx);
      //
      //    List<char*>* curTestEls = new List<char*>();
      //
      //    for (uint32_t testElIdx = 0; testElIdx < numElements; testElIdx++) {
      //
      //      if (testElIdx == baseElIdx) {
      //        continue;
      //      }
      //
      //      CollisionDataEntry* testEl = _collisionDataStore->get(testElIdx);
      //
      //      if (
      //        (
      //          (
      //            (baseEl->horzPos > testEl->horzPos) && (baseEl->horzPos < testEl->horzPos + testEl->width) &&
      //            (baseEl->vertPos > testEl->vertPos) && (baseEl->vertPos < testEl->vertPos + testEl->height)
      //          ) || (
      //            (baseEl->horzPos + baseEl->width > testEl->horzPos) && (baseEl->horzPos + baseEl->width < testEl->horzPos + testEl->width) &&
      //            (baseEl->vertPos + baseEl->height > testEl->vertPos) && (baseEl->vertPos + baseEl->height < testEl->vertPos + testEl->height)
      //          )
      //        ) || (
      //          (
      //            (testEl->horzPos > baseEl->horzPos) && (testEl->horzPos < baseEl->horzPos + baseEl->width) &&
      //            (testEl->vertPos > baseEl->vertPos) && (testEl->vertPos < baseEl->vertPos + baseEl->height)
      //          ) || (
      //            (testEl->horzPos + testEl->width > baseEl->horzPos) && (testEl->horzPos + testEl->width < baseEl->horzPos + baseEl->width) &&
      //            (testEl->vertPos + testEl->height > baseEl->vertPos) && (testEl->vertPos + testEl->height < baseEl->vertPos + baseEl->height)
      //          )
      //        )
      //      ) {
      //        //void*(*baseElCallback)(void*, void*, void*) = baseEl->callback;
      //        //void*(*testElCallback)(void*, void*, void*) = testEl->callback;
      //
      //
      //        printf("\n\nCOLLLLLIIIIISION1!!1!!!!!!!!11\n\n");
      //
      //        //baseElCallback(NULL, NULL, NULL);
      //        //testElCallback(NULL, NULL, NULL);
      //      }
      //
      //    }
      //
      //  }
      //
      //  //return retList;
      //}

  };


#endif
