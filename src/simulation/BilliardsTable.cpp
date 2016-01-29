#include "BilliardsTable.h"

BilliardsTable::BilliardsTable(RectangleBoundingObject boundingRectangle)
        : boundingRectangle{boundingRectangle},
          model(ResourceManager::getModel("billiards_table")) { }

void BilliardsTable::draw() {
    Matrix translation = Matrix(Vector(tableModelDeltaX, tableModelDeltaY, 0.0));
    Matrix rotation = Matrix(Vector(0.0, 1.0, 0.0), (float) (M_PI / 2.0));
    Matrix scale = Matrix::scaleMatrix(Vector(tableModelScaleX,
                                              (tableModelScaleX + tableModelScaleY) / 2.0f,
                                              tableModelScaleY));
    Matrix modelMat = rotation * translation * scale;

    model->draw(ResourceManager::getShader("default"), modelMat);
}
