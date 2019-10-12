//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "Base.h"

@implementation Base
@synthesize curShownOnScreen;
@synthesize initFrame;

-(instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if(self){
        self.initFrame = frame;
        curShownOnScreen = false;
    }
    return self;
}

-(void)dealloc{
    [super dealloc];
}

@end
