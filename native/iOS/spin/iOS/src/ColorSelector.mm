//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "ColorSelector.h"
#import "Helper.h"

@implementation ColorSelector

-(instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if(self){
        colorBox = nil;
        innerBoxElement = nil;
        descriptionL = nil;
        [self addComponents];
    }
    return self;
}

-(void)addComponents{
    UIColor *color = [Helper getGrayColor];
    int offsetY = [Helper screenBorderOffset];
    int height = [Helper buttonSize].height*0.5;
    
    [Helper releaseViewObject:&innerBoxElement];
    [Helper releaseViewObject:&colorBox];
    colorBox = [[UIView alloc]initWithFrame:CGRectMake((self.frame.size.width - height)*0.5, offsetY, height, height)];
    colorBox.layer.cornerRadius = height * 0.15;
    colorBox.layer.borderWidth = 1;
    colorBox.layer.borderColor = [color CGColor];
    colorBox.userInteractionEnabled = false;
    //INNER ELEMENT
    int innerBoxHeight = height *0.7;
    innerBoxElement = [[UIView alloc]initWithFrame:CGRectMake((colorBox.frame.size.width - innerBoxHeight)*0.5,
                                                              (height-innerBoxHeight)*0.5,
                                                              innerBoxHeight,
                                                              innerBoxHeight)];
    innerBoxElement.layer.cornerRadius = innerBoxHeight * 0.15;
    innerBoxElement.backgroundColor = color;
    innerBoxElement.userInteractionEnabled = false;
    [colorBox addSubview:innerBoxElement];
    [self addSubview:colorBox];
    
    offsetY += (colorBox.frame.size.height + colorBox.frame.origin.y - [Helper screenBorderOffset]) * 0.9 ;
    height = self.frame.size.height - (colorBox.frame.size.height + colorBox.frame.origin.y);
    
    [Helper releaseViewObject:&descriptionL];
    descriptionL = [[UILabel alloc]initWithFrame:CGRectMake(0, offsetY, self.frame.size.width, height)];
    descriptionL.text = [Helper colorText];
    descriptionL.textAlignment = NSTextAlignmentCenter;
    descriptionL.textColor = color;
    descriptionL.font = [UIFont fontWithName:@"HelveticaNeue" size: height*0.35];
    descriptionL.numberOfLines = 2;
    descriptionL.userInteractionEnabled = false;
    [self addSubview:descriptionL];
}

-(void)setColor:(int)color{
    if(innerBoxElement != nil){
        innerBoxElement.backgroundColor = [Helper getIUColorFromHex:color];
    }
}



-(void)dealloc{
    [Helper releaseViewObject:&innerBoxElement];
    [Helper releaseViewObject:&colorBox];
    [Helper releaseViewObject:&descriptionL];
    [super dealloc];
}

@end
