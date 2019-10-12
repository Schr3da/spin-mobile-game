//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "RankingCell.h"
#import "Helper.h"

@implementation RankingCell

-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if(self != nil){
        titleL = nil;
        positionL = nil;
        valueL = nil;
        
        [Helper releaseViewObject:&titleL];
        CGRect labelFrame = CGRectMake(0, 0, self.frame.size.width, self.frame.size.height);
        labelFrame.origin.x = [Helper screenBorderOffset]*0.5;
        titleL = [[UILabel alloc]initWithFrame:labelFrame];
        titleL.textColor = [Helper getGrayColor];
        titleL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:self.textLabel.font.lineHeight];
        titleL.hidden = true;
        [self addSubview:titleL];
        self.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    return self;
}

-(void)addComponents{
    
    int intent = [Helper screenBorderOffset]*0.5;
    int height = [Helper largeCellHeight];
    
    [Helper releaseViewObject:&positionL];
    positionL = [[UILabel alloc]initWithFrame:CGRectMake(intent, 0, self.frame.size.width*0.5, height)];
    positionL.textColor = [Helper getGrayColor];
    positionL.textAlignment = NSTextAlignmentLeft;
    positionL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size: self.textLabel.font.lineHeight];
    [self addSubview:positionL];
    
    [Helper releaseViewObject:&valueL];
    valueL = [[UILabel alloc]initWithFrame:CGRectMake(self.frame.size.width *0.5, 0, self.frame.size.width*0.5 - intent, height)];
    valueL.textColor = [Helper getGrayColor];
    valueL.textAlignment = NSTextAlignmentRight;
    valueL.font = [UIFont fontWithName:@"HelveticaNeue-Thin" size:height *0.5*0.9];
    [self addSubview:valueL];
}


-(void)setValueLabelText:(NSString *)text{
    if(valueL == nil){
        return;
    }
    valueL.text = (text != nil) ? text : @"";
}

-(void)setPositionLabelText:(NSString *)text{
    if(positionL == nil){
        return;
    }
    positionL.text = (text != nil) ? text : @"";
}

-(void)setTitleText:(NSString *)text color:(UIColor *)color{
    if(titleL == nil){
        return;
    }
    titleL.hidden = false;
    titleL.textColor = color;
    titleL.text = (text != nil) ? text : @"";
}

-(void)dealloc{
    [Helper releaseViewObject:&titleL];
    [Helper releaseViewObject:&positionL];
    [Helper releaseViewObject:&valueL];
    [super dealloc];
}

@end
