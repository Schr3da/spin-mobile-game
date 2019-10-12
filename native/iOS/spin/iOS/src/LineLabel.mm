//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "LineLabel.h"
#import "Helper.h"

@implementation LineLabel

-(instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if(self){
        _information = nil;
        _description = nil;
        self.userInteractionEnabled = false;
    }
    return self;
}

-(void)addLabelWithTitle:(NSString *)information description:(NSString *)description{
    UIColor *color = [Helper getGrayColor];
    int offsetY = 0;
    int height = self.frame.size.height *0.5;
    
    _information = [[UILabel alloc]initWithFrame:CGRectMake(0, offsetY, self.frame.size.width, height)];
    _information.text = information;
    _information.textAlignment = NSTextAlignmentCenter;
    _information.textColor = color;
    _information.font = [UIFont fontWithName:@"HelveticaNeue-Light" size: height*0.9];
    _information.userInteractionEnabled = false;
    [self addSubview:_information];
    
    offsetY += (_information.frame.size.height + _information.frame.origin.y) * 0.9;
    height = self.frame.size.height - (_information.frame.size.height + _information.frame.origin.y);
    
    _description = [[UILabel alloc]initWithFrame:CGRectMake(0, offsetY, self.frame.size.width, height)];
    _description.text = description;
    _description.textAlignment = NSTextAlignmentCenter;
    _description.textColor = color;
    _description.font = [UIFont fontWithName:@"HelveticaNeue" size: height*0.35];
    _description.numberOfLines = 2;
    _description.userInteractionEnabled = false;
    [self addSubview:_description];
}


-(NSString *)getInformation{
    return _information.text;
}

-(void)setInformation:(NSString *)text{
    if(_information != nil){
        _information.text = text;
    }
}

-(NSString *)getDescription{
    return _description.text;
}

-(void)setDescription:(NSString *)text{
    if(_information != nil){
        _description.text = text;
    }
}

-(void)setColor:(UIColor *)color{
    if(_information == nil || _description == nil){
        return;
    }
    _information.textColor = color;
    //_description.textColor = color;
}

-(void)dealloc{
    [Helper releaseViewObject:&_information];
    [Helper releaseViewObject:&_description];
    [super dealloc];
}

@end
