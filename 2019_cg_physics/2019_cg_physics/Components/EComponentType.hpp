/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

enum class EComponentType
{
    // Offset begins at 1
    Position,
    Movement,
    Drawing,
    View,
    // ... add here more Component-Types
    
    MaxItem, // Do not delete or move this line, because it defines the amount of Components.
};
