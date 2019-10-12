//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "ImageView.h"

@implementation ImageView
@synthesize initMatrix;

-(instancetype)initWithFrame:(CGRect)frame{
    
    self = [super initWithFrame:frame];
    if(self != nil){
        initMatrix = self.transform;
    }
    return self;
}

@end
